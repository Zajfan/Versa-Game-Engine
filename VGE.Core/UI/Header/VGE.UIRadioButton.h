#ifndef UIRADIOBUTTON_H
#define UIRADIOBUTTON_H

#include "UIElement.h"
#include <string>
#include <vector>

class UIRadioButtonGroup; // Forward declaration

class UIRadioButton : public UIElement
{
public:
    UIRadioButton(const std::string& text, UIRadioButtonGroup* group);

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::string Text;
    bool IsChecked = false;
    UIRadioButtonGroup* Group; // Pointer to the radio button group this button belongs to

private:
    // ... (Helper functions or member variables)
};


class UIRadioButtonGroup
{
public:
    UIRadioButtonGroup();

    void AddButton(UIRadioButton* button);
    void RemoveButton(UIRadioButton* button);
    void SetSelectedButton(UIRadioButton* button);

private:
    std::vector<UIRadioButton*> buttons_;
};

#endif // UIRADIOBUTTON_H