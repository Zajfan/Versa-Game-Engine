// UIButton.h (Example UI element class)

#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UIElement.h"

class UIButton : public UIElement
{
public:
    UIButton(const std::string& text);

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::string Text;

private:
    // ... (Helper functions or member variables)
};

#endif // UIBUTTON_H