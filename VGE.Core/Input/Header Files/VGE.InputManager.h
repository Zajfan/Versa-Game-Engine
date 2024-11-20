#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

namespace VGE {

enum class Key {
    UNKNOWN,
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
    ESCAPE, LCONTROL, LSHIFT, LALT, LSYSTEM, RCONTROL, RSHIFT, RALT, RSYSTEM,
    MENU, LBRACKET, RBRACKET, SEMICOLON, COMMA, PERIOD, QUOTE, SLASH, BACKSLASH,
    TILDE, EQUAL, DASH, SPACE, RETURN, BACKSPACE, TAB, PAGEUP, PAGEDOWN, END,
    HOME, INSERT, DELETE, ADD, SUBTRACT, MULTIPLY, DIVIDE,
    LEFT, RIGHT, UP, DOWN,
    NUMPAD_0, NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    PAUSE
};

enum class MouseButton {
    LEFT,
    RIGHT,
    MIDDLE,
    XBUTTON1,
    XBUTTON2
};

struct InputEvent {
    Key key;
    MouseButton mouseButton;
    bool pressed;
};

class InputManager {
public:
    using KeyCallback = std::function<void(const InputEvent&)>;

    void registerKeyCallback(Key key, KeyCallback callback);
    void registerMouseCallback(MouseButton button, KeyCallback callback);
    void processInputEvents();

private:
    std::unordered_map<Key, std::vector<KeyCallback>> m_keyCallbacks;
    std::unordered_map<MouseButton, std::vector<KeyCallback>> m_mouseCallbacks;
    std::vector<InputEvent> m_eventQueue;
};

} // namespace VGE
