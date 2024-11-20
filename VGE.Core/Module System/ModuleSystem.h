#pragma once

#include "VGE.Core.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace VGE {

// Forward declarations
class IModule;

// Module dependency information
struct ModuleDependency {
    std::string moduleName;
    Version minimumVersion;
    bool isOptional;
};

// Module information
struct ModuleInfo {
    std::string name;
    Version version;
    std::vector<ModuleDependency> dependencies;
    bool isLoaded{false};
    bool isCore{false};
};

// Module loading/unloading events
class ModuleEvent : public Event {
public:
    enum class Type {
        LOAD_START,
        LOAD_SUCCESS,
        LOAD_FAILED,
        UNLOAD_START,
        UNLOAD_SUCCESS,
        UNLOAD_FAILED
    };

    ModuleEvent(Type type, const std::string& moduleName) 
        : m_type(type), m_moduleName(moduleName) {}

    const char* getType() const override {
        switch (m_type) {
            case Type::LOAD_START: return "MODULE_LOAD_START";
            case Type::LOAD_SUCCESS: return "MODULE_LOAD_SUCCESS";
            case Type::LOAD_FAILED: return "MODULE_LOAD_FAILED";
            case Type::UNLOAD_START: return "MODULE_UNLOAD_START";
            case Type::UNLOAD_SUCCESS: return "MODULE_UNLOAD_SUCCESS";
            case Type::UNLOAD_FAILED: return "MODULE_UNLOAD_FAILED";
            default: return "UNKNOWN";
        }
    }

    const std::string& getModuleName() const { return m_moduleName; }

private:
    Type m_type;
    std::string m_moduleName;
};

// Module Manager class
class ModuleManager {
public:
    ModuleManager() = default;
    ~ModuleManager() = default;

    bool initialize();
    void shutdown();

    // Module operations
    bool loadModule(const std::string& name);
    bool unloadModule(const std::string& name);
    bool reloadModule(const std::string& name);

    // Module queries
    IModule* getModule(const std::string& name);
    const ModuleInfo* getModuleInfo(const std::string& name) const;
    std::vector<std::string> getLoadedModules() const;
    std::vector<ModuleDependency> getDependencies(const std::string& name) const;

    // Module registration
    bool registerModule(std::unique_ptr<IModule> module, const ModuleInfo& info);
    void unregisterModule(const std::string& name);

    // Dependency management
    bool checkDependencies(const std::string& name) const;
    std::vector<std::string> getModuleLoadOrder() const;

private:
    bool loadModuleInternal(const std::string& name, std::vector<std::string>& loadedModules);
    bool unloadModuleInternal(const std::string& name, std::vector<std::string>& unloadedModules);
    bool hasCyclicDependencies(const std::string& name, std::vector<std::string>& visited) const;

    std::unordered_map<std::string, std::unique_ptr<IModule>> m_modules;
    std::unordered_map<std::string, ModuleInfo> m_moduleInfo;
    bool m_initialized{false};
};

} // namespace VGE
