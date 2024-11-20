#include "../Header Files/VGE.Core.h"
#include <sstream>
#include <stdexcept>

namespace VGE {

std::string Version::toString() const {
    std::stringstream ss;
    ss << major << "." << minor << "." << patch;
    return ss.str();
}

// Singleton instance
Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

bool Engine::initialize(const EngineConfig& config) {
    if (m_initialized) {
        return false;
    }

    m_version = config.version;

    // Initialize memory manager
    m_memoryManager = std::make_unique<MemoryManager>();
    if (!m_memoryManager->initialize(config.defaultMemoryPoolSize)) {
        return false;
    }

    // Initialize event system
    m_eventSystem = std::make_unique<EventSystem>();
    if (!m_eventSystem->initialize()) {
        return false;
    }

    m_initialized = true;
    return true;
}

void Engine::shutdown() {
    if (!m_initialized) {
        return;
    }

    // Shutdown plugins in reverse order
    for (auto it = m_plugins.rbegin(); it != m_plugins.rend(); ++it) {
        it->second->shutdown();
    }
    m_plugins.clear();

    // Shutdown modules in reverse order
    for (auto it = m_modules.rbegin(); it != m_modules.rend(); ++it) {
        it->second->shutdown();
    }
    m_modules.clear();

    // Shutdown core systems
    if (m_eventSystem) {
        m_eventSystem->shutdown();
        m_eventSystem.reset();
    }

    if (m_memoryManager) {
        m_memoryManager->shutdown();
        m_memoryManager.reset();
    }

    m_initialized = false;
}

bool Engine::registerModule(std::unique_ptr<IModule> module) {
    if (!module) {
        return false;
    }

    const char* name = module->getName();
    if (m_modules.find(name) != m_modules.end()) {
        return false;
    }

    if (!module->initialize()) {
        return false;
    }

    m_modules[name] = std::move(module);
    return true;
}

bool Engine::loadPlugin(const std::string& path) {
    // TODO: Implement dynamic library loading
    return false;
}

bool Engine::unloadPlugin(const std::string& name) {
    auto it = m_plugins.find(name);
    if (it == m_plugins.end()) {
        return false;
    }

    it->second->shutdown();
    m_plugins.erase(it);
    return true;
}

IMemoryAllocator* Engine::getMemoryAllocator() {
    return m_memoryManager.get();
}

void Engine::addEventListener(const std::string& eventType, IEventListener* listener) {
    if (m_eventSystem) {
        m_eventSystem->addEventListener(eventType, listener);
    }
}

void Engine::removeEventListener(const std::string& eventType, IEventListener* listener) {
    if (m_eventSystem) {
        m_eventSystem->removeEventListener(eventType, listener);
    }
}

void Engine::dispatchEvent(const Event& event) {
    if (m_eventSystem) {
        m_eventSystem->dispatchEvent(event);
    }
}

bool Engine::isInitialized() const {
    return m_initialized;
}

const Version& Engine::getVersion() const {
    return m_version;
}

} // namespace VGE
