#ifndef UISlider_H
#define UISlider_H

#include "UIElement.h"

class UISlider : public UIElement
{
public:
    UISlider(float minValue, float maxValue);

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    float MinValue;
    float MaxValue;
    float CurrentValue;

private:
    // ... (Helper functions or member variables)
    // For example:
    // - bool isDragging = false;
    // - glm::vec2 sliderPosition; // Position of the slider knob
};

#endif // UISlider_H