#ifndef UICHECKBOX_H
#define UICHECKBOX_H

#include "UIElement.h"

class UICheckbox : public UIElement
{
public:
    UICheckbox(const std::string& text);

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::string Text;
    bool IsChecked = false;

private:
    // ... (Helper functions or member variables)
};

#endif // UICHECKBOX_H