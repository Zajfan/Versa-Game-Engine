#pragma once

#include "VGE.Core.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace VGE {

// Forward declarations
class DynamicLibrary;

// Plugin manifest information
struct PluginManifest {
    std::string name;
    std::string description;
    Version version;
    std::string author;
    std::string website;
    std::vector<std::string> dependencies;
    std::string entryPoint;
    bool supportsHotReload{false};
};

// Plugin state information
struct PluginState {
    bool isLoaded{false};
    bool isEnabled{false};
    std::string error;
    std::unique_ptr<DynamicLibrary> library;
    PluginManifest manifest;
    IPlugin* instance{nullptr};
};

// Plugin events
class PluginEvent : public Event {
public:
    enum class Type {
        LOAD_START,
        LOAD_SUCCESS,
        LOAD_FAILED,
        UNLOAD_START,
        UNLOAD_SUCCESS,
        UNLOAD_FAILED,
        ENABLE,
        DISABLE,
        HOT_RELOAD_START,
        HOT_RELOAD_SUCCESS,
        HOT_RELOAD_FAILED
    };

    PluginEvent(Type type, const std::string& pluginName) 
        : m_type(type), m_pluginName(pluginName) {}

    const char* getType() const override {
        switch (m_type) {
            case Type::LOAD_START: return "PLUGIN_LOAD_START";
            case Type::LOAD_SUCCESS: return "PLUGIN_LOAD_SUCCESS";
            case Type::LOAD_FAILED: return "PLUGIN_LOAD_FAILED";
            case Type::UNLOAD_START: return "PLUGIN_UNLOAD_START";
            case Type::UNLOAD_SUCCESS: return "PLUGIN_UNLOAD_SUCCESS";
            case Type::UNLOAD_FAILED: return "PLUGIN_UNLOAD_FAILED";
            case Type::ENABLE: return "PLUGIN_ENABLE";
            case Type::DISABLE: return "PLUGIN_DISABLE";
            case Type::HOT_RELOAD_START: return "PLUGIN_HOT_RELOAD_START";
            case Type::HOT_RELOAD_SUCCESS: return "PLUGIN_HOT_RELOAD_SUCCESS";
            case Type::HOT_RELOAD_FAILED: return "PLUGIN_HOT_RELOAD_FAILED";
            default: return "UNKNOWN";
        }
    }

    const std::string& getPluginName() const { return m_pluginName; }

private:
    Type m_type;
    std::string m_pluginName;
};

// Plugin function types
using CreatePluginFunc = IPlugin* (*)();
using DestroyPluginFunc = void (*)(IPlugin*);

// Dynamic library wrapper
class DynamicLibrary {
public:
    DynamicLibrary(const std::string& path);
    ~DynamicLibrary();

    bool isLoaded() const;
    void* getSymbol(const std::string& name) const;
    const std::string& getError() const;

private:
    void* m_handle{nullptr};
    std::string m_error;
};

// Plugin Manager class
class PluginManager {
public:
    PluginManager() = default;
    ~PluginManager() = default;

    bool initialize(const std::string& pluginDirectory);
    void shutdown();

    // Plugin operations
    bool loadPlugin(const std::string& path);
    bool unloadPlugin(const std::string& name);
    bool enablePlugin(const std::string& name);
    bool disablePlugin(const std::string& name);
    bool reloadPlugin(const std::string& name);

    // Plugin queries
    IPlugin* getPlugin(const std::string& name);
    const PluginManifest* getPluginManifest(const std::string& name) const;
    std::vector<std::string> getLoadedPlugins() const;
    std::vector<std::string> getEnabledPlugins() const;

    // Plugin discovery
    std::vector<std::string> discoverPlugins() const;
    bool validatePlugin(const std::string& path) const;
    PluginManifest loadManifest(const std::string& path) const;

    // Hot reloading
    void enableHotReload(bool enable);
    void checkForUpdates();

private:
    bool loadPluginInternal(const std::string& path, PluginState& state);
    bool unloadPluginInternal(PluginState& state);
    bool checkDependencies(const PluginManifest& manifest) const;
    void watchPluginDirectory();
    void processHotReload();

    std::string m_pluginDirectory;
    std::unordered_map<std::string, PluginState> m_plugins;
    bool m_hotReloadEnabled{false};
    bool m_initialized{false};
};

} // namespace VGE
