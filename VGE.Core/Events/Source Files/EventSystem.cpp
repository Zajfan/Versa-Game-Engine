#include "../Header Files/EventSystem.h"
#include <algorithm>

namespace VGE {

bool EventSystem::initialize() {
    if (m_initialized) {
        return false;
    }

    m_initialized = true;
    return true;
}

void EventSystem::shutdown() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_listeners.clear();
    m_initialized = false;
}

void EventSystem::addEventListener(const std::string& eventType, IEventListener* listener) {
    if (!listener) return;

    std::lock_guard<std::mutex> lock(m_mutex);
    auto& listeners = m_listeners[eventType];
    
    // Check if listener already exists
    if (std::find(listeners.begin(), listeners.end(), listener) == listeners.end()) {
        listeners.push_back(listener);
    }
}

void EventSystem::removeEventListener(const std::string& eventType, IEventListener* listener) {
    if (!listener) return;

    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_listeners.find(eventType);
    if (it != m_listeners.end()) {
        auto& listeners = it->second;
        listeners.erase(
            std::remove(listeners.begin(), listeners.end(), listener),
            listeners.end()
        );

        // Remove the event type if no listeners remain
        if (listeners.empty()) {
            m_listeners.erase(it);
        }
    }
}

void EventSystem::dispatchEvent(const Event& event) {
    if (!event.getType()) return;

    std::vector<IEventListener*> listenersToNotify;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_listeners.find(event.getType());
        if (it != m_listeners.end()) {
            listenersToNotify = it->second;
        }
    }

    // Notify listeners outside the lock to prevent deadlocks
    for (auto listener : listenersToNotify) {
        if (listener) {
            listener->onEvent(event);
        }
    }
}

size_t EventSystem::getListenerCount(const std::string& eventType) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_listeners.find(eventType);
    return it != m_listeners.end() ? it->second.size() : 0;
}

std::vector<std::string> EventSystem::getRegisteredEventTypes() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<std::string> types;
    types.reserve(m_listeners.size());
    
    for (const auto& pair : m_listeners) {
        types.push_back(pair.first);
    }
    
    return types;
}

} // namespace VGE
