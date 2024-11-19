// VGE.UIElement.cpp

#include "VGE.UIElement.h"

UIElement::UIElement()
    : Position(0.0f, 0.0f), Size(0.0f, 0.0f), Color(1.0f, 1.0f, 1.0f, 1.0f),
    IsVisible(true), IsEnabled(true), m_position(0.0f, 0.0f), m_size(0.0f, 0.0f), m_color(1.0f, 1.0f, 1.0f, 1.0f)
{
    // Constructor implementation
}

UIElement::~UIElement()
{
    // Destructor implementation
}

void UIElement::SetPosition(const glm::vec2& position)
{
    Position = position;
}

void UIElement::SetSize(const glm::vec2& size)
{
    Size = size;
}

void UIElement::SetColor(const glm::vec4& color)
{
    Color = color;
}

void UIElement::SetVisible(bool visible)
{
    IsVisible = visible;
}

void UIElement::SetEnabled(bool enabled)
{
    IsEnabled = enabled;
}

void UIElement::AddChild(std::shared_ptr<UIElement> child)
{
    m_children.push_back(child);
}

void UIElement::RemoveChild(std::shared_ptr<UIElement> child)
{
    m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
}

void UIElement::ClearChildren()
{
    m_children.clear();
}
