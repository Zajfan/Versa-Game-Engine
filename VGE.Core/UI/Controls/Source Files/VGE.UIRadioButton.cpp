#include "../Header Files/VGE.UIRadioButton.h"
#include <iostream>

UIRadioButton::UIRadioButton(const std::string& text, UIRadioButtonGroup* group)
    : Text(text), IsChecked(false), Group(group) {
    if (Group) {
        Group->AddButton(this);
    }
}

void UIRadioButton::Render(OpenGLRenderer& renderer) {
    // Render the radio button using OpenGL
    renderer.DrawCheckbox(glm::vec2(10.0f, 10.0f), IsChecked, Text, glm::vec3(0.5f, 0.5f, 0.5f));
    std::cout << "Rendering UIRadioButton with text: " << Text << " and state: " << (IsChecked ? "Checked" : "Unchecked") << std::endl;
    // Add OpenGL rendering code here
}

bool UIRadioButton::HandleInput(const InputEvent& event) {
    // Handle input events to toggle the radio button state
    std::cout << "Handling input for UIRadioButton" << std::endl;
    if (/* condition to check input event */) {
        if (Group) {
            Group->SetSelectedButton(this);
        }
        std::cout << "RadioButton state changed to: Checked" << std::endl;
        return true;
    }
    return false; // Return true if the event was handled
}

UIRadioButtonGroup::UIRadioButtonGroup() {}

void UIRadioButtonGroup::AddButton(UIRadioButton* button) {
    buttons_.push_back(button);
}

void UIRadioButtonGroup::RemoveButton(UIRadioButton* button) {
    buttons_.erase(std::remove(buttons_.begin(), buttons_.end(), button), buttons_.end());
}

void UIRadioButtonGroup::SetSelectedButton(UIRadioButton* button) {
    for (auto& btn : buttons_) {
        btn->IsChecked = (btn == button);
    }
}
