// UIManager.h

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>
#include <memory>
#include "UIElement.h"
#include "OpenGLRenderer.h" // Or your renderer class
#include "InputEvent.h" // Or your input event class

class UIManager
{
public:
    UIManager();
    ~UIManager();

    void Update(float deltaTime);
    void Render(OpenGLRenderer& renderer); // Or your renderer class
    bool HandleInput(const InputEvent& event);

    // Methods to add and remove UI elements
    void AddElement(std::unique_ptr<UIElement> element);
    void RemoveElement(UIElement* element);

    // Getter for UI elements (for rendering)
    const std::vector<std::unique_ptr<UIElement>>& GetElements() const { return elements_; }

private:
    std::vector<std::unique_ptr<UIElement>> elements_;
};

#endif // UIMANAGER_H