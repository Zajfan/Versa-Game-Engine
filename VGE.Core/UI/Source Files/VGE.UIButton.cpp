// Last modified on: 30/07/2020 10:00 Change the time and date as required
// File: VGE.UIButton.cpp
// Description: Implementation file for the VGE_UIButton class.

// include the necessary header files
#include "VGE.UIButton.h"
#include "VGE.OpenGLRenderer.h"
#include "VGE.UIElement.h"

// Include Text related headers
// Includes for text rendering and layout functionalities.
#include "VGE.TextAlignment.h"
#include "VGE.TextWrapping.h"
#include "VGE.TextOverflow.h"
#include "VGE.TextClipping.h"
#include "VGE.TextTransformation.h"

// Include standard headers
#include <iostream>
#include <string>
#include <glm/glm.hpp>

namespace VGE
{
	// Constructor
	UIButton::UIButton(std::string text, glm::vec2 position, glm::vec2 size, glm::vec4 color, glm::vec4 textColor, TextAlignment alignment)
		: UIElement(position, size, color), m_text(text), m_textColor(textColor), m_alignment(alignment)
	{
	}
	// Destructor
	UIButton::~UIButton()
	{
	}
	// Draw the button
	void UIButton::Draw(OpenGLRenderer* renderer)
	{
		// Set the color of the button
		renderer->SetDrawColor(m_color);
		// Draw the button
		renderer->DrawRect(m_position, m_size);
		// Set the color of the text
		renderer->SetDrawColor(m_textColor);
		// Draw the text
		renderer->DrawText(m_text, m_position, m_size, m_alignment);
	}
	// Set the text of the button
	void UIButton::SetText(std::string text)
	{
		m_text = text;
	}
	// Get the text of the button
	std::string UIButton::GetText() const
	{
		return m_text;
	}
	// Set the text color of the button
	void UIButton::SetTextColor(glm::vec4 color)
	{
		m_textColor = color;
	}
	// Get the text color of the button
	glm::vec4 UIButton::GetTextColor() const
	{
		return m_textColor;
	}
	// Set the alignment of the text
	void UIButton::SetAlignment(TextAlignment alignment)
	{
		m_alignment = alignment;
	}
	// Get the alignment of the text
	TextAlignment UIButton::GetAlignment() const
	{
		return m_alignment;
	}
}