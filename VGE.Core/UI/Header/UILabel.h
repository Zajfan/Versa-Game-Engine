#ifndef UILABEL_H
#define UILABEL_H

#include "UIElement.h"
#include <string>

class UILabel : public UIElement
{
public:
    UILabel(const std::string& text);

    void Render(OpenGLRenderer& renderer) override;
    // You might not need to override HandleInput if the label is not interactive

    // Properties
    std::string Text;
    std::string FontName = "Arial"; // Default font
    int FontSize = 12; // Default font size
    glm::vec3 TextColor = glm::vec3(0.0f, 0.0f, 0.0f); // Default color (black)

private:
    // ... (Helper functions or member variables)
    // For example:
    // - unsigned int fontTextureID; // To store the OpenGL texture ID for the font
};

#endif // UILABEL_H