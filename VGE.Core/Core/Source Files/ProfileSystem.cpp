#include "../Header Files/ProfileSystem.h"
#include <fstream>
#include <thread>
#include <sstream>
#include <iomanip>
#include <json.hpp>

namespace VGE {

using json = nlohmann::json;

// ProfileSession implementation
ProfileSession::ProfileSession(const std::string& name)
    : m_name(name) {}

ProfileSession::~ProfileSession() {}

void ProfileSession::addEvent(const ProfileEvent& event) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_events.push_back(event);
}

void ProfileSession::addMemoryEvent(const MemoryEvent& event) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_memoryEvents.push_back(event);
}

void ProfileSession::setMetadata(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_metadata[key] = value;
}

// ProfileMarker implementation
ProfileMarker::ProfileMarker(const std::string& name, const std::string& category)
    : m_name(name), m_category(category), m_startTime(std::chrono::high_resolution_clock::now()) {}

ProfileMarker::~ProfileMarker() {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Duration>(endTime - m_startTime);

    ProfileEvent event{
        m_name,
        m_startTime,
        duration,
        std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())),
        0, // depth will be calculated by the ProfileManager
        m_category,
        m_metadata
    };

    ProfileManager::getInstance().recordEvent(event);
}

void ProfileMarker::addMetadata(const std::string& key, const std::string& value) {
    m_metadata[key] = value;
}

// ProfileManager implementation
ProfileManager& ProfileManager::getInstance() {
    static ProfileManager instance;
    return instance;
}

void ProfileManager::initialize() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_initialized) return;

    cleanup();
    m_initialized = true;
}

void ProfileManager::shutdown() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_initialized) return;

    stopSession();
    cleanup();
    m_initialized = false;
}

void ProfileManager::startSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_initialized) return;

    stopSession();
    m_currentSession = std::make_unique<ProfileSession>(name);
}

void ProfileManager::stopSession() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return;

    m_sessions[m_currentSession->getName()] = std::move(m_currentSession);
}

void ProfileManager::pauseSession() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_paused = true;
}

void ProfileManager::resumeSession() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_paused = false;
}

void ProfileManager::recordEvent(const ProfileEvent& event) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_initialized || !m_currentSession || m_paused) return;

    m_currentSession->addEvent(event);
}

void ProfileManager::recordMemoryEvent(const MemoryEvent& event) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_initialized || !m_currentSession || m_paused) return;

    m_currentSession->addMemoryEvent(event);
}

ProfileSession* ProfileManager::getCurrentSession() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_currentSession.get();
}

std::vector<std::string> ProfileManager::getSessionNames() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<std::string> names;
    for (const auto& pair : m_sessions) {
        names.push_back(pair.first);
    }
    return names;
}

ProfileSession* ProfileManager::getSession(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_sessions.find(name);
    return it != m_sessions.end() ? it->second.get() : nullptr;
}

double ProfileManager::getAverageEventDuration(const std::string& eventName) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return 0.0;

    const auto& events = m_currentSession->getEvents();
    size_t count = 0;
    Duration totalDuration(0);

    for (const auto& event : events) {
        if (event.name == eventName) {
            totalDuration += event.duration;
            count++;
        }
    }

    return count > 0 ? 
        std::chrono::duration<double>(totalDuration).count() / count : 0.0;
}

size_t ProfileManager::getTotalMemoryAllocated() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return 0;

    const auto& memEvents = m_currentSession->getMemoryEvents();
    size_t total = 0;

    for (const auto& event : memEvents) {
        if (event.type == MemoryEvent::Type::ALLOC) {
            total += event.size;
        } else if (event.type == MemoryEvent::Type::FREE) {
            total -= event.size;
        }
    }

    return total;
}

size_t ProfileManager::getPeakMemoryUsage() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return 0;

    const auto& memEvents = m_currentSession->getMemoryEvents();
    size_t current = 0;
    size_t peak = 0;

    for (const auto& event : memEvents) {
        if (event.type == MemoryEvent::Type::ALLOC) {
            current += event.size;
            peak = std::max(peak, current);
        } else if (event.type == MemoryEvent::Type::FREE) {
            current -= event.size;
        }
    }

    return peak;
}

std::vector<ProfileEvent> ProfileManager::getEventsByCategory(const std::string& category) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return {};

    std::vector<ProfileEvent> result;
    const auto& events = m_currentSession->getEvents();

    for (const auto& event : events) {
        if (event.category == category) {
            result.push_back(event);
        }
    }

    return result;
}

std::vector<MemoryEvent> ProfileManager::getMemoryEventsByCategory(const std::string& category) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return {};

    std::vector<MemoryEvent> result;
    const auto& events = m_currentSession->getMemoryEvents();

    for (const auto& event : events) {
        if (event.category == category) {
            result.push_back(event);
        }
    }

    return result;
}

void ProfileManager::captureGpuUsage() {
    // Placeholder for GPU usage capture logic
    // Integrate with platform-specific APIs to gather GPU metrics
}

void ProfileManager::captureDiskIO() {
    // Placeholder for disk I/O capture logic
    // Integrate with platform-specific APIs to gather disk I/O metrics
}

void ProfileManager::captureNetworkActivity() {
    // Placeholder for network activity capture logic
    // Integrate with platform-specific APIs to gather network metrics
}

void ProfileManager::exportToJson(const std::string& filename) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return;

    json j;
    j["name"] = m_currentSession->getName();
    j["metadata"] = m_currentSession->getMetadata();

    // Export events
    json events = json::array();
    for (const auto& event : m_currentSession->getEvents()) {
        json e;
        e["name"] = event.name;
        e["startTime"] = std::chrono::duration_cast<std::chrono::microseconds>(
            event.startTime.time_since_epoch()).count();
        e["duration"] = std::chrono::duration_cast<std::chrono::microseconds>(
            event.duration).count();
        e["threadId"] = event.threadId;
        e["depth"] = event.depth;
        e["category"] = event.category;
        e["metadata"] = event.metadata;
        events.push_back(e);
    }
    j["events"] = events;

    // Export memory events
    json memEvents = json::array();
    for (const auto& event : m_currentSession->getMemoryEvents()) {
        json e;
        e["type"] = static_cast<int>(event.type);
        e["size"] = event.size;
        e["address"] = reinterpret_cast<uintptr_t>(event.address);
        e["threadId"] = event.threadId;
        e["timestamp"] = std::chrono::duration_cast<std::chrono::microseconds>(
            event.timestamp.time_since_epoch()).count();
        e["category"] = event.category;
        e["stackTrace"] = event.stackTrace;
        memEvents.push_back(e);
    }
    j["memoryEvents"] = memEvents;

    // Add additional metrics
    j["cpu_usage"] = 0.0; // captureCpuUsage();
    j["gpu_usage"] = 0.0; // captureGpuUsage();
    j["disk_io"] = 0.0; // captureDiskIO();
    j["network_activity"] = 0.0; // captureNetworkActivity();

    // Write to file
    std::ofstream file(filename);
    file << std::setw(4) << j << std::endl;
}

void ProfileManager::exportToChrome(const std::string& filename) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return;

    json j;
    j["traceEvents"] = json::array();

    // Convert events to Chrome Tracing format
    for (const auto& event : m_currentSession->getEvents()) {
        json e;
        e["name"] = event.name;
        e["cat"] = event.category;
        e["ph"] = "X"; // Complete Event
        e["pid"] = 1; // Process ID
        e["tid"] = std::stoi(event.threadId); // Thread ID
        e["ts"] = std::chrono::duration_cast<std::chrono::microseconds>(
            event.startTime.time_since_epoch()).count();
        e["dur"] = std::chrono::duration_cast<std::chrono::microseconds>(
            event.duration).count();
        j["traceEvents"].push_back(e);
    }

    // Add additional events and metrics for better visualization

    // Write to file
    std::ofstream file(filename);
    file << std::setw(4) << j << std::endl;
}

void ProfileManager::exportToCSV(const std::string& filename) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_currentSession) return;

    std::ofstream file(filename);
    file << "Name,Category,ThreadId,StartTime,Duration,Depth\n";

    for (const auto& event : m_currentSession->getEvents()) {
        file << event.name << ","
             << event.category << ","
             << event.threadId << ","
             << std::chrono::duration_cast<std::chrono::microseconds>(
                    event.startTime.time_since_epoch()).count() << ","
             << std::chrono::duration_cast<std::chrono::microseconds>(
                    event.duration).count() << ","
             << event.depth << "\n";
    }

    // Add additional metrics
    file << "CPU Usage," << 0.0 << "\n"; // captureCpuUsage();
    file << "GPU Usage," << 0.0 << "\n"; // captureGpuUsage();
    file << "Disk I/O," << 0.0 << "\n"; // captureDiskIO();
    file << "Network Activity," << 0.0 << "\n"; // captureNetworkActivity();
}

void ProfileManager::cleanup() {
    m_currentSession.reset();
    m_sessions.clear();
    m_paused = false;
}

} // namespace VGE
