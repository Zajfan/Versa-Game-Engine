#pragma once

#include "VGE.Core.h"
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <memory>
#include <mutex>

namespace VGE {

// Forward declarations
class ProfileSession;
class ProfileMarker;

// Profile data types
using TimePoint = std::chrono::high_resolution_clock::time_point;
using Duration = std::chrono::nanoseconds;

// Profile event data
struct ProfileEvent {
    std::string name;
    TimePoint startTime;
    Duration duration;
    std::string threadId;
    size_t depth;
    std::string category;
    std::unordered_map<std::string, std::string> metadata;
};

// Memory allocation event
struct MemoryEvent {
    enum class Type {
        ALLOC,
        FREE,
        REALLOC
    };

    Type type;
    size_t size;
    void* address;
    std::string threadId;
    TimePoint timestamp;
    std::string category;
    std::string stackTrace;
};

// Profile session data
class ProfileSession {
public:
    ProfileSession(const std::string& name);
    ~ProfileSession();

    void addEvent(const ProfileEvent& event);
    void addMemoryEvent(const MemoryEvent& event);
    void setMetadata(const std::string& key, const std::string& value);

    const std::string& getName() const { return m_name; }
    const std::vector<ProfileEvent>& getEvents() const { return m_events; }
    const std::vector<MemoryEvent>& getMemoryEvents() const { return m_memoryEvents; }
    const std::unordered_map<std::string, std::string>& getMetadata() const { return m_metadata; }

private:
    std::string m_name;
    std::vector<ProfileEvent> m_events;
    std::vector<MemoryEvent> m_memoryEvents;
    std::unordered_map<std::string, std::string> m_metadata;
    std::mutex m_mutex;
};

// Scoped profile marker
class ProfileMarker {
public:
    ProfileMarker(const std::string& name, const std::string& category = "Default");
    ~ProfileMarker();

    void addMetadata(const std::string& key, const std::string& value);

private:
    std::string m_name;
    std::string m_category;
    TimePoint m_startTime;
    std::unordered_map<std::string, std::string> m_metadata;
};

// Profile manager class
class ProfileManager {
public:
    static ProfileManager& getInstance();

    void initialize();
    void shutdown();

    // Session management
    void startSession(const std::string& name);
    void stopSession();
    void pauseSession();
    void resumeSession();

    // Event recording
    void recordEvent(const ProfileEvent& event);
    void recordMemoryEvent(const MemoryEvent& event);

    // Data access
    ProfileSession* getCurrentSession();
    std::vector<std::string> getSessionNames() const;
    ProfileSession* getSession(const std::string& name);

    // Analysis
    double getAverageEventDuration(const std::string& eventName) const;
    size_t getTotalMemoryAllocated() const;
    size_t getPeakMemoryUsage() const;
    std::vector<ProfileEvent> getEventsByCategory(const std::string& category) const;
    std::vector<MemoryEvent> getMemoryEventsByCategory(const std::string& category) const;

    // Export
    void exportToJson(const std::string& filename) const;
    void exportToChrome(const std::string& filename) const;
    void exportToCSV(const std::string& filename) const;

private:
    ProfileManager() = default;
    ~ProfileManager() = default;

    ProfileManager(const ProfileManager&) = delete;
    ProfileManager& operator=(const ProfileManager&) = delete;

    void cleanup();

    std::unique_ptr<ProfileSession> m_currentSession;
    std::unordered_map<std::string, std::unique_ptr<ProfileSession>> m_sessions;
    bool m_initialized{false};
    bool m_paused{false};
    std::mutex m_mutex;
};

// Convenience macros for profiling
#ifdef VGE_ENABLE_PROFILING
    #define VGE_PROFILE_FUNCTION() VGE::ProfileMarker __profiler(__FUNCTION__)
    #define VGE_PROFILE_SCOPE(name) VGE::ProfileMarker __profiler(name)
    #define VGE_PROFILE_CATEGORY(name, category) VGE::ProfileMarker __profiler(name, category)
#else
    #define VGE_PROFILE_FUNCTION()
    #define VGE_PROFILE_SCOPE(name)
    #define VGE_PROFILE_CATEGORY(name, category)
#endif

} // namespace VGE
