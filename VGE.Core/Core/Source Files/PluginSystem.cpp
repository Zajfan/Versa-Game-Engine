#include "../Header Files/PluginSystem.h"
#include <filesystem>
#include <fstream>
#include <json.hpp> // Using nlohmann/json for manifest parsing

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace VGE {

namespace fs = std::filesystem;
using json = nlohmann::json;

// DynamicLibrary implementation
DynamicLibrary::DynamicLibrary(const std::string& path) {
#ifdef _WIN32
    m_handle = LoadLibraryA(path.c_str());
    if (!m_handle) {
        DWORD error = GetLastError();
        char* message = nullptr;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr,
            error,
            0,
            reinterpret_cast<LPSTR>(&message),
            0,
            nullptr
        );
        m_error = message ? message : "Unknown error";
        LocalFree(message);
    }
#else
    m_handle = dlopen(path.c_str(), RTLD_NOW);
    if (!m_handle) {
        m_error = dlerror();
    }
#endif
}

DynamicLibrary::~DynamicLibrary() {
    if (m_handle) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(m_handle));
#else
        dlclose(m_handle);
#endif
    }
}

bool DynamicLibrary::isLoaded() const {
    return m_handle != nullptr;
}

void* DynamicLibrary::getSymbol(const std::string& name) const {
    if (!m_handle) return nullptr;

#ifdef _WIN32
    return reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(m_handle), name.c_str()));
#else
    return dlsym(m_handle, name.c_str());
#endif
}

const std::string& DynamicLibrary::getError() const {
    return m_error;
}

// PluginManager implementation
bool PluginManager::initialize(const std::string& pluginDirectory) {
    if (m_initialized) {
        return false;
    }

    m_pluginDirectory = pluginDirectory;
    if (!fs::exists(m_pluginDirectory)) {
        try {
            fs::create_directories(m_pluginDirectory);
        } catch (const std::exception&) {
            return false;
        }
    }

    m_initialized = true;
    return true;
}

void PluginManager::shutdown() {
    // Unload all plugins in reverse load order
    std::vector<std::string> pluginNames;
    for (const auto& pair : m_plugins) {
        if (pair.second.isLoaded) {
            pluginNames.push_back(pair.first);
        }
    }

    for (auto it = pluginNames.rbegin(); it != pluginNames.rend(); ++it) {
        unloadPlugin(*it);
    }

    m_plugins.clear();
    m_initialized = false;
}

bool PluginManager::loadPlugin(const std::string& path) {
    if (!m_initialized) return false;

    // Load and validate manifest
    PluginManifest manifest = loadManifest(path);
    if (manifest.name.empty()) {
        return false;
    }

    // Check if plugin is already loaded
    auto it = m_plugins.find(manifest.name);
    if (it != m_plugins.end() && it->second.isLoaded) {
        return false;
    }

    // Check dependencies
    if (!checkDependencies(manifest)) {
        return false;
    }

    // Create plugin state
    PluginState state;
    state.manifest = std::move(manifest);

    // Dispatch load start event
    Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::LOAD_START, state.manifest.name));

    // Load the plugin
    bool success = loadPluginInternal(path, state);

    // Store state and dispatch appropriate event
    if (success) {
        m_plugins[state.manifest.name] = std::move(state);
        Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::LOAD_SUCCESS, state.manifest.name));
    } else {
        Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::LOAD_FAILED, state.manifest.name));
    }

    return success;
}

bool PluginManager::loadPluginInternal(const std::string& path, PluginState& state) {
    // Load dynamic library
    state.library = std::make_unique<DynamicLibrary>(path);
    if (!state.library->isLoaded()) {
        state.error = state.library->getError();
        return false;
    }

    // Get create/destroy functions
    auto createFunc = reinterpret_cast<CreatePluginFunc>(
        state.library->getSymbol(state.manifest.entryPoint + "_create")
    );
    auto destroyFunc = reinterpret_cast<DestroyPluginFunc>(
        state.library->getSymbol(state.manifest.entryPoint + "_destroy")
    );

    if (!createFunc || !destroyFunc) {
        state.error = "Failed to find plugin entry points";
        return false;
    }

    // Create plugin instance
    state.instance = createFunc();
    if (!state.instance) {
        state.error = "Failed to create plugin instance";
        return false;
    }

    state.isLoaded = true;
    return true;
}

bool PluginManager::unloadPlugin(const std::string& name) {
    auto it = m_plugins.find(name);
    if (it == m_plugins.end() || !it->second.isLoaded) {
        return false;
    }

    // Dispatch unload start event
    Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::UNLOAD_START, name));

    // Unload the plugin
    bool success = unloadPluginInternal(it->second);

    // Dispatch appropriate event
    PluginEvent::Type eventType = success ? PluginEvent::Type::UNLOAD_SUCCESS : PluginEvent::Type::UNLOAD_FAILED;
    Engine::getInstance().dispatchEvent(PluginEvent(eventType, name));

    if (success) {
        m_plugins.erase(it);
    }

    return success;
}

bool PluginManager::unloadPluginInternal(PluginState& state) {
    if (!state.isLoaded || !state.instance) {
        return false;
    }

    // Get destroy function
    auto destroyFunc = reinterpret_cast<DestroyPluginFunc>(
        state.library->getSymbol(state.manifest.entryPoint + "_destroy")
    );

    if (destroyFunc) {
        destroyFunc(state.instance);
    }

    state.instance = nullptr;
    state.library.reset();
    state.isLoaded = false;
    return true;
}

bool PluginManager::enablePlugin(const std::string& name) {
    auto it = m_plugins.find(name);
    if (it == m_plugins.end() || !it->second.isLoaded || it->second.isEnabled) {
        return false;
    }

    if (!it->second.instance->initialize(Engine::getInstance().getConfig())) {
        return false;
    }

    it->second.isEnabled = true;
    Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::ENABLE, name));
    return true;
}

bool PluginManager::disablePlugin(const std::string& name) {
    auto it = m_plugins.find(name);
    if (it == m_plugins.end() || !it->second.isLoaded || !it->second.isEnabled) {
        return false;
    }

    it->second.instance->shutdown();
    it->second.isEnabled = false;
    Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::DISABLE, name));
    return true;
}

bool PluginManager::reloadPlugin(const std::string& name) {
    auto it = m_plugins.find(name);
    if (it == m_plugins.end() || !it->second.isLoaded) {
        return false;
    }

    if (!it->second.manifest.supportsHotReload) {
        return false;
    }

    // Dispatch hot reload start event
    Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::HOT_RELOAD_START, name));

    // Store the plugin path
    std::string pluginPath = it->second.manifest.name; // This should be the full path

    // Unload the plugin
    if (!unloadPlugin(name)) {
        Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::HOT_RELOAD_FAILED, name));
        return false;
    }

    // Load the plugin again
    if (!loadPlugin(pluginPath)) {
        Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::HOT_RELOAD_FAILED, name));
        return false;
    }

    Engine::getInstance().dispatchEvent(PluginEvent(PluginEvent::Type::HOT_RELOAD_SUCCESS, name));
    return true;
}

IPlugin* PluginManager::getPlugin(const std::string& name) {
    auto it = m_plugins.find(name);
    return (it != m_plugins.end() && it->second.isLoaded) ? it->second.instance : nullptr;
}

const PluginManifest* PluginManager::getPluginManifest(const std::string& name) const {
    auto it = m_plugins.find(name);
    return (it != m_plugins.end()) ? &it->second.manifest : nullptr;
}

std::vector<std::string> PluginManager::getLoadedPlugins() const {
    std::vector<std::string> result;
    for (const auto& pair : m_plugins) {
        if (pair.second.isLoaded) {
            result.push_back(pair.first);
        }
    }
    return result;
}

std::vector<std::string> PluginManager::getEnabledPlugins() const {
    std::vector<std::string> result;
    for (const auto& pair : m_plugins) {
        if (pair.second.isLoaded && pair.second.isEnabled) {
            result.push_back(pair.first);
        }
    }
    return result;
}

std::vector<std::string> PluginManager::discoverPlugins() const {
    std::vector<std::string> result;
    
    try {
        for (const auto& entry : fs::recursive_directory_iterator(m_pluginDirectory)) {
            if (entry.is_regular_file() && validatePlugin(entry.path().string())) {
                result.push_back(entry.path().string());
            }
        }
    } catch (const std::exception&) {
        // Handle directory iteration errors
    }

    return result;
}

bool PluginManager::validatePlugin(const std::string& path) const {
    // Check file extension
#ifdef _WIN32
    if (fs::path(path).extension() != ".dll") return false;
#else
    if (fs::path(path).extension() != ".so") return false;
#endif

    // Validate manifest
    return !loadManifest(path).name.empty();
}

PluginManifest PluginManager::loadManifest(const std::string& path) const {
    PluginManifest manifest;
    
    try {
        // Look for manifest file next to the plugin
        std::string manifestPath = fs::path(path).replace_extension(".json").string();
        if (!fs::exists(manifestPath)) {
            return manifest;
        }

        // Read and parse manifest file
        std::ifstream file(manifestPath);
        json j = json::parse(file);

        manifest.name = j["name"].get<std::string>();
        manifest.description = j["description"].get<std::string>();
        manifest.version = Version{
            j["version"]["major"].get<int>(),
            j["version"]["minor"].get<int>(),
            j["version"]["patch"].get<int>()
        };
        manifest.author = j["author"].get<std::string>();
        manifest.website = j["website"].get<std::string>();
        manifest.dependencies = j["dependencies"].get<std::vector<std::string>>();
        manifest.entryPoint = j["entryPoint"].get<std::string>();
        manifest.supportsHotReload = j["supportsHotReload"].get<bool>();

    } catch (const std::exception&) {
        // Handle manifest parsing errors
        manifest = PluginManifest();
    }

    return manifest;
}

bool PluginManager::checkDependencies(const PluginManifest& manifest) const {
    for (const auto& dep : manifest.dependencies) {
        auto it = m_plugins.find(dep);
        if (it == m_plugins.end() || !it->second.isLoaded) {
            return false;
        }
    }
    return true;
}

void PluginManager::enableHotReload(bool enable) {
    m_hotReloadEnabled = enable;
    if (enable) {
        watchPluginDirectory();
    }
}

void PluginManager::checkForUpdates() {
    if (!m_hotReloadEnabled) return;
    processHotReload();
}

void PluginManager::watchPluginDirectory() {
    // TODO: Implement file system watcher for plugins
    // Similar to AssetManager's watchAssetDirectory
}

void PluginManager::processHotReload() {
    // TODO: Implement hot reload processing for plugins
    // Similar to AssetManager's processHotReload
}

} // namespace VGE
