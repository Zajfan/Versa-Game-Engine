#include "../Header Files/VGE.InputManager.h"
#include <iostream>

namespace VGE {

void InputManager::registerKeyCallback(Key key, KeyCallback callback) {
    m_keyCallbacks[key].push_back(callback);
}

void InputManager::registerMouseCallback(MouseButton button, KeyCallback callback) {
    m_mouseCallbacks[button].push_back(callback);
}

void InputManager::processInputEvents() {
    for (const auto& event : m_eventQueue) {
        if (event.key != Key::UNKNOWN) {
            auto it = m_keyCallbacks.find(event.key);
            if (it != m_keyCallbacks.end()) {
                for (const auto& callback : it->second) {
                    callback(event);
                }
            }
        }
        if (event.mouseButton != MouseButton::LEFT) { // Assuming LEFT as default
            auto it = m_mouseCallbacks.find(event.mouseButton);
            if (it != m_mouseCallbacks.end()) {
                for (const auto& callback : it->second) {
                    callback(event);
                }
            }
        }
    }
    m_eventQueue.clear();
}

} // namespace VGE
