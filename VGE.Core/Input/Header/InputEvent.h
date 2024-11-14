#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <glm/glm.hpp> // Or your preferred math library

enum class InputEventType
{
    Undefined,
    KeyDown,
    KeyUp,
    MouseDown,
    MouseUp,
    MouseMove,
    MouseWheel,
    // ... add other input event types as needed
};

class InputEvent
{
public:
    InputEvent(InputEventType type);

    InputEventType Type() const { return type_; }

    // Key events
    int KeyCode() const { return keyCode_; }
    void SetKeyCode(int keyCode) { keyCode_ = keyCode; }

    // Mouse events
    glm::vec2 MousePosition() const { return mousePosition_; }
    void SetMousePosition(const glm::vec2& position) { mousePosition_ = position; }
    int MouseButton() const { return mouseButton_; }
    void SetMouseButton(int button) { mouseButton_ = button; }
    int MouseWheelDelta() const { return mouseWheelDelta_; }
    void SetMouseWheelDelta(int delta) { mouseWheelDelta_ = delta; }

private:
    InputEventType type_;

    // Key event data
    int keyCode_;

    // Mouse event data
    glm::vec2 mousePosition_;
    int mouseButton_;
    int mouseWheelDelta_;

    // ... add other event data as needed
};

#endif // INPUTEVENT_H