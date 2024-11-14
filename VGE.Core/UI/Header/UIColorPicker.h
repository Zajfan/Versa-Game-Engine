#ifndef UICOLORPICKER_H
#define UICOLORPICKER_H

#include "UIElement.h"
#include <glm/glm.hpp> // Or your preferred color representation

class UIColorPicker : public UIElement
{
public:
    UIColorPicker();

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    glm::vec3 SelectedColor = glm::vec3(1.0f, 1.0f, 1.0f); // Default to white

private:
    // ... (Helper functions or member variables)
    // For example:
    // - bool IsDraggingHueSlider = false;
    // - bool IsDraggingSaturationValueArea = false;
    // - glm::vec2 HueSliderPosition;
    // - glm::vec2 SaturationValuePosition;
};

#endif // UICOLORPICKER_H