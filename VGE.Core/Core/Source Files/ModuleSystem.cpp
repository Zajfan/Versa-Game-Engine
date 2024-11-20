#include "../Header Files/ModuleSystem.h"
#include <algorithm>
#include <queue>
#include <set>

namespace VGE {

bool ModuleManager::initialize() {
    if (m_initialized) {
        return false;
    }

    m_initialized = true;
    return true;
}

void ModuleManager::shutdown() {
    // Unload all modules in reverse dependency order
    auto loadOrder = getModuleLoadOrder();
    std::reverse(loadOrder.begin(), loadOrder.end());

    for (const auto& moduleName : loadOrder) {
        unloadModule(moduleName);
    }

    m_modules.clear();
    m_moduleInfo.clear();
    m_initialized = false;
}

bool ModuleManager::loadModule(const std::string& name) {
    if (!m_initialized) return false;

    // Check if module is already loaded
    auto infoIt = m_moduleInfo.find(name);
    if (infoIt == m_moduleInfo.end()) {
        return false;
    }

    if (infoIt->second.isLoaded) {
        return true;
    }

    // Dispatch load start event
    Engine::getInstance().dispatchEvent(ModuleEvent(ModuleEvent::Type::LOAD_START, name));

    // Load module and its dependencies
    std::vector<std::string> loadedModules;
    bool success = loadModuleInternal(name, loadedModules);

    // Dispatch appropriate event based on result
    ModuleEvent::Type eventType = success ? ModuleEvent::Type::LOAD_SUCCESS : ModuleEvent::Type::LOAD_FAILED;
    Engine::getInstance().dispatchEvent(ModuleEvent(eventType, name));

    return success;
}

bool ModuleManager::loadModuleInternal(const std::string& name, std::vector<std::string>& loadedModules) {
    // Check for cyclic dependencies
    std::vector<std::string> visited;
    if (hasCyclicDependencies(name, visited)) {
        return false;
    }

    auto infoIt = m_moduleInfo.find(name);
    if (infoIt == m_moduleInfo.end()) {
        return false;
    }

    // First load dependencies
    for (const auto& dep : infoIt->second.dependencies) {
        if (!dep.isOptional) {
            if (!loadModuleInternal(dep.moduleName, loadedModules)) {
                return false;
            }
        }
    }

    // Load the module itself
    auto moduleIt = m_modules.find(name);
    if (moduleIt == m_modules.end()) {
        return false;
    }

    if (!moduleIt->second->initialize()) {
        return false;
    }

    infoIt->second.isLoaded = true;
    loadedModules.push_back(name);
    return true;
}

bool ModuleManager::unloadModule(const std::string& name) {
    if (!m_initialized) return false;

    auto infoIt = m_moduleInfo.find(name);
    if (infoIt == m_moduleInfo.end() || !infoIt->second.isLoaded) {
        return false;
    }

    // Dispatch unload start event
    Engine::getInstance().dispatchEvent(ModuleEvent(ModuleEvent::Type::UNLOAD_START, name));

    // Unload module and its dependents
    std::vector<std::string> unloadedModules;
    bool success = unloadModuleInternal(name, unloadedModules);

    // Dispatch appropriate event based on result
    ModuleEvent::Type eventType = success ? ModuleEvent::Type::UNLOAD_SUCCESS : ModuleEvent::Type::UNLOAD_FAILED;
    Engine::getInstance().dispatchEvent(ModuleEvent(eventType, name));

    return success;
}

bool ModuleManager::unloadModuleInternal(const std::string& name, std::vector<std::string>& unloadedModules) {
    // First find all modules that depend on this one
    std::vector<std::string> dependents;
    for (const auto& pair : m_moduleInfo) {
        for (const auto& dep : pair.second.dependencies) {
            if (dep.moduleName == name && !dep.isOptional) {
                dependents.push_back(pair.first);
                break;
            }
        }
    }

    // Unload dependent modules first
    for (const auto& dependent : dependents) {
        if (!unloadModuleInternal(dependent, unloadedModules)) {
            return false;
        }
    }

    // Unload the module itself
    auto moduleIt = m_modules.find(name);
    if (moduleIt == m_modules.end()) {
        return false;
    }

    moduleIt->second->shutdown();
    m_moduleInfo[name].isLoaded = false;
    unloadedModules.push_back(name);
    return true;
}

bool ModuleManager::reloadModule(const std::string& name) {
    if (!unloadModule(name)) {
        return false;
    }
    return loadModule(name);
}

IModule* ModuleManager::getModule(const std::string& name) {
    auto it = m_modules.find(name);
    return it != m_modules.end() ? it->second.get() : nullptr;
}

const ModuleInfo* ModuleManager::getModuleInfo(const std::string& name) const {
    auto it = m_moduleInfo.find(name);
    return it != m_moduleInfo.end() ? &it->second : nullptr;
}

std::vector<std::string> ModuleManager::getLoadedModules() const {
    std::vector<std::string> result;
    for (const auto& pair : m_moduleInfo) {
        if (pair.second.isLoaded) {
            result.push_back(pair.first);
        }
    }
    return result;
}

std::vector<ModuleDependency> ModuleManager::getDependencies(const std::string& name) const {
    auto it = m_moduleInfo.find(name);
    return it != m_moduleInfo.end() ? it->second.dependencies : std::vector<ModuleDependency>();
}

bool ModuleManager::registerModule(std::unique_ptr<IModule> module, const ModuleInfo& info) {
    if (!module || info.name.empty()) {
        return false;
    }

    if (m_modules.find(info.name) != m_modules.end()) {
        return false;
    }

    m_modules[info.name] = std::move(module);
    m_moduleInfo[info.name] = info;
    return true;
}

void ModuleManager::unregisterModule(const std::string& name) {
    if (m_moduleInfo[name].isLoaded) {
        unloadModule(name);
    }
    m_modules.erase(name);
    m_moduleInfo.erase(name);
}

bool ModuleManager::checkDependencies(const std::string& name) const {
    auto it = m_moduleInfo.find(name);
    if (it == m_moduleInfo.end()) {
        return false;
    }

    for (const auto& dep : it->second.dependencies) {
        if (dep.isOptional) continue;

        auto depIt = m_moduleInfo.find(dep.moduleName);
        if (depIt == m_moduleInfo.end()) {
            return false;
        }

        if (depIt->second.version.major < dep.minimumVersion.major ||
            (depIt->second.version.major == dep.minimumVersion.major && 
             depIt->second.version.minor < dep.minimumVersion.minor)) {
            return false;
        }
    }

    return true;
}

std::vector<std::string> ModuleManager::getModuleLoadOrder() const {
    std::vector<std::string> result;
    std::set<std::string> visited;
    std::set<std::string> visiting;

    // Helper function for topological sort
    std::function<bool(const std::string&)> visit = [&](const std::string& name) {
        if (visited.find(name) != visited.end()) {
            return true;
        }
        if (visiting.find(name) != visiting.end()) {
            return false; // Cyclic dependency detected
        }

        visiting.insert(name);

        auto it = m_moduleInfo.find(name);
        if (it != m_moduleInfo.end()) {
            for (const auto& dep : it->second.dependencies) {
                if (!dep.isOptional && !visit(dep.moduleName)) {
                    return false;
                }
            }
        }

        visiting.erase(name);
        visited.insert(name);
        result.push_back(name);
        return true;
    };

    // Visit all modules
    for (const auto& pair : m_moduleInfo) {
        if (!visit(pair.first)) {
            return std::vector<std::string>(); // Return empty vector on cyclic dependency
        }
    }

    return result;
}

bool ModuleManager::hasCyclicDependencies(const std::string& name, std::vector<std::string>& visited) const {
    if (std::find(visited.begin(), visited.end(), name) != visited.end()) {
        return true;
    }

    visited.push_back(name);

    auto it = m_moduleInfo.find(name);
    if (it != m_moduleInfo.end()) {
        for (const auto& dep : it->second.dependencies) {
            if (!dep.isOptional && hasCyclicDependencies(dep.moduleName, visited)) {
                return true;
            }
        }
    }

    visited.pop_back();
    return false;
}

} // namespace VGE
