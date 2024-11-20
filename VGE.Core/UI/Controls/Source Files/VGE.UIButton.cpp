// Last modified on: 30/07/2020 10:00 Change the time and date as required
// File: VGE.UIButton.cpp
// Description: Implementation file for the VGE_UIButton class.
#include "VGE.UIButton.h"
#include "VGE.OpenGLRenderer.h"
#include "VGE.UIElement.h"
#include "VGE.TextAlignment.h"

// Include standard headers
#include <iostream>
#include <string>
#include <glm/glm.hpp>

namespace VGE
{
    UIButton::UIButton(std::string text, glm::vec2 position, glm::vec2 size, glm::vec4 color, glm::vec4 textColor, TextAlignment alignment)
        : UIElement(), m_text(text), m_textColor(textColor), m_alignment(alignment)
    {
        Position = position;
        Size = size;
        Color = color;
    }

    UIButton::~UIButton() {}

    void UIButton::Render(OpenGLRenderer& renderer)
    {
        renderer.DrawButton(Position, Size, m_text, glm::vec3(Color.r, Color.g, Color.b));
    }

    void UIButton::SetText(std::string text)
    {
        m_text = text;
    }

    std::string UIButton::GetText() const
    {
        return m_text;
    }

    void UIButton::SetTextColor(glm::vec4 color)
    {
        m_textColor = color;
    }

    glm::vec4 UIButton::GetTextColor() const
    {
        return m_textColor;
    }

    void UIButton::SetAlignment(TextAlignment alignment)
    {
        m_alignment = alignment;
    }

    TextAlignment UIButton::GetAlignment() const
    {
        return m_alignment;
    }
}