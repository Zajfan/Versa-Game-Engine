#include "../Header Files/VGE.UICheckbox.h"
#include <iostream>

UICheckbox::UICheckbox(const std::string& text)
    : Text(text), IsChecked(false) {}

void UICheckbox::Render(OpenGLRenderer& renderer) {
    // Render the checkbox using OpenGL
    renderer.DrawCheckbox(glm::vec2(10.0f, 10.0f), IsChecked, Text, glm::vec3(0.5f, 0.5f, 0.5f));
    // Add additional OpenGL rendering code here if needed
}

bool UICheckbox::HandleInput(const InputEvent& event) {
    // Handle input events to toggle the checkbox state
    std::cout << "Handling input for UICheckbox" << std::endl;
    if (/* condition to check input event */) {
        IsChecked = !IsChecked;
        std::cout << "Checkbox state changed to: " << (IsChecked ? "Checked" : "Unchecked") << std::endl;
        return true;
    }
    return false; // Return true if the event was handled
}

// Additional helper functions or member variables can be implemented here
