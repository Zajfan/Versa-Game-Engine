#ifndef UIPROGRESSBAR_H
#define UIPROGRESSBAR_H

#include "UIElement.h"

class UIProgressBar : public UIElement
{
public:
    UIProgressBar();

    void Render(OpenGLRenderer& renderer) override;
    // You might not need to override HandleInput if the progress bar is not interactive

    // Properties
    float Progress = 0.0f; // Range: 0.0 to 1.0
    glm::vec3 BarColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default color (green)

private:
    // ... (Helper functions or member variables)
};

#endif // UIPROGRESSBAR_H