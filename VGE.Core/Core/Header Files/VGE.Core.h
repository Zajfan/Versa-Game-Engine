#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace VGE {

// Forward declarations
class IModule;
class IPlugin;
class MemoryManager;
class EventSystem;

// Version information
struct Version {
    int major;
    int minor;
    int patch;
    std::string toString() const;
};

// Core engine configuration
struct EngineConfig {
    Version version{1, 0, 0};
    size_t defaultMemoryPoolSize = 1024 * 1024 * 1024; // 1GB default
    bool enableProfiling = true;
    bool enableDebugLogging = true;
};

// Memory Management
class IMemoryAllocator {
public:
    virtual ~IMemoryAllocator() = default;
    virtual void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) = 0;
    virtual void deallocate(void* ptr) = 0;
};

// Module Interface
class IModule {
public:
    virtual ~IModule() = default;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    virtual const char* getName() const = 0;
    virtual Version getVersion() const = 0;
};

// Plugin Interface
class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual bool initialize(const EngineConfig& config) = 0;
    virtual void shutdown() = 0;
    virtual const char* getName() const = 0;
    virtual Version getVersion() const = 0;
};

// Event System
class Event {
public:
    virtual ~Event() = default;
    virtual const char* getType() const = 0;
};

class IEventListener {
public:
    virtual ~IEventListener() = default;
    virtual void onEvent(const Event& event) = 0;
};

// Core Engine Class
class Engine {
public:
    static Engine& getInstance();
    
    bool initialize(const EngineConfig& config);
    void shutdown();
    
    // Module Management
    template<typename T>
    T* getModule();
    bool registerModule(std::unique_ptr<IModule> module);
    
    // Plugin Management
    bool loadPlugin(const std::string& path);
    bool unloadPlugin(const std::string& name);
    
    // Memory Management
    IMemoryAllocator* getMemoryAllocator();
    
    // Event System
    void addEventListener(const std::string& eventType, IEventListener* listener);
    void removeEventListener(const std::string& eventType, IEventListener* listener);
    void dispatchEvent(const Event& event);
    
    // Engine State
    bool isInitialized() const;
    const Version& getVersion() const;
    
private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    
    std::unique_ptr<MemoryManager> m_memoryManager;
    std::unique_ptr<EventSystem> m_eventSystem;
    std::unordered_map<std::string, std::unique_ptr<IModule>> m_modules;
    std::unordered_map<std::string, std::unique_ptr<IPlugin>> m_plugins;
    bool m_initialized = false;
    Version m_version;
};

} // namespace VGE