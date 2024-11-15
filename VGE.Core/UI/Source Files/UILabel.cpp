#include "UILabel.h"
#include "OpenGLRenderer.h" // Include your OpenGL renderer

UILabel::UILabel(const std::string& text) : Text(text) {}

void UILabel::Render(OpenGLRenderer& renderer)
{
    if (!IsVisible)
        return;

    // 1. Calculate position and size
    glm::vec2 textPosition = Position; // Start with the label's position

    // Apply horizontal alignment
    float textWidth = renderer.GetTextWidth(Text, FontName, FontSize); // You'll need to implement this in your renderer
    switch (HorizontalAlignment)
    {
    case Alignment::Center:
        textPosition.x += (Size.x - textWidth) / 2.0f;
        break;
    case Alignment::Right:
        textPosition.x += Size.x - textWidth;
        break;
    default: // Left alignment
        break;
    }

    // Apply vertical alignment (assuming text is rendered from the baseline)
    float textHeight = renderer.GetTextHeight(FontName, FontSize); // You'll need to implement this in your renderer
    switch (VerticalAlignment)
    {
    case Alignment::Center:
        textPosition.y += (Size.y - textHeight) / 2.0f;
        break;
    case Alignment::Bottom:
        textPosition.y += Size.y - textHeight;
        break;
    default: // Top alignment
        break;
    }

    // 2. Render the text using the renderer
    renderer.DrawText(Text, textPosition, FontName, FontSize, TextColor);
}