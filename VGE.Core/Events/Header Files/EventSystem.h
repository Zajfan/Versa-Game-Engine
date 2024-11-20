#pragma once

#include "VGE.Core.h"
#include <unordered_map>
#include <vector>
#include <mutex>

namespace VGE {

class EventSystem {
public:
    EventSystem() = default;
    ~EventSystem() = default;

    bool initialize();
    void shutdown();

    void addEventListener(const std::string& eventType, IEventListener* listener);
    void removeEventListener(const std::string& eventType, IEventListener* listener);
    void dispatchEvent(const Event& event);

    // Event statistics
    size_t getListenerCount(const std::string& eventType) const;
    std::vector<std::string> getRegisteredEventTypes() const;

private:
    std::unordered_map<std::string, std::vector<IEventListener*>> m_listeners;
    mutable std::mutex m_mutex;
    bool m_initialized{false};
};

// Common engine events
class EngineEvent : public Event {
public:
    enum class Type {
        ENGINE_INIT,
        ENGINE_SHUTDOWN,
        MODULE_LOADED,
        MODULE_UNLOADED,
        PLUGIN_LOADED,
        PLUGIN_UNLOADED,
        MEMORY_WARNING,
        PERFORMANCE_WARNING
    };

    EngineEvent(Type type) : m_type(type) {}

    const char* getType() const override {
        switch (m_type) {
            case Type::ENGINE_INIT: return "ENGINE_INIT";
            case Type::ENGINE_SHUTDOWN: return "ENGINE_SHUTDOWN";
            case Type::MODULE_LOADED: return "MODULE_LOADED";
            case Type::MODULE_UNLOADED: return "MODULE_UNLOADED";
            case Type::PLUGIN_LOADED: return "PLUGIN_LOADED";
            case Type::PLUGIN_UNLOADED: return "PLUGIN_UNLOADED";
            case Type::MEMORY_WARNING: return "MEMORY_WARNING";
            case Type::PERFORMANCE_WARNING: return "PERFORMANCE_WARNING";
            default: return "UNKNOWN";
        }
    }

private:
    Type m_type;
};

} // namespace VGE
