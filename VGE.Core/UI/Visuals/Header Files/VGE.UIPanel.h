#ifndef UIPANEL_H
#define UIPANEL_H

#include "UIElement.h"
#include <vector>
#include <memory>

class UIPanel : public UIElement
{
public:
    UIPanel();

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;
    void Update(float deltaTime) override;

    // Methods to add and remove child UI elements
    void AddChild(std::unique_ptr<UIElement> child);
    void RemoveChild(UIElement* child);

private:
    std::vector<std::unique_ptr<UIElement>> children_;
};

#endif // UIPANEL_H