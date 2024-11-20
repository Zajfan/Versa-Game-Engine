#include "../Header Files/VGE.UISlider.h"
#include <iostream>

UISlider::UISlider(float minValue, float maxValue)
    : MinValue(minValue), MaxValue(maxValue), CurrentValue(minValue) {}

void UISlider::Render(OpenGLRenderer& renderer) {
    // Render the slider using OpenGL
    renderer.DrawSlider(glm::vec2(10.0f, 10.0f), MinValue, MaxValue, CurrentValue, glm::vec3(0.5f, 0.5f, 0.5f));
    // Add additional OpenGL rendering code here if needed
}

bool UISlider::HandleInput(const InputEvent& event) {
    // Handle input events to update the slider's current value
    std::cout << "Handling input for UISlider" << std::endl;
    // Update CurrentValue based on input
    return false; // Return true if the event was handled
}

// Additional helper functions or member variables can be implemented here
