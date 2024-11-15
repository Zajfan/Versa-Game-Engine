// UIElement.h (Base class for all UI elements)

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <glm/glm.hpp> // Or your preferred math library
#include <string>

class UIElement
{
public:
    enum class Alignment { Left, Center, Right, Bottom };

    UIElement();
    virtual ~UIElement() = default;

    virtual void Update(float deltaTime);
    virtual void Render(class OpenGLRenderer& renderer); // Or your renderer class
    virtual bool HandleInput(const class InputEvent& event);

    // Properties
    glm::vec2 Position;
    glm::vec2 Size;
    glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f); // White by default
    std::string Name;
    bool IsVisible = true;
    bool IsEnabled = true;
    Alignment HorizontalAlignment = Alignment::Left;
    Alignment VerticalAlignment = Alignment::Center;

protected:
    // Helper functions for rendering, input handling, etc.
    // ...
};

#endif // UIELEMENT_H