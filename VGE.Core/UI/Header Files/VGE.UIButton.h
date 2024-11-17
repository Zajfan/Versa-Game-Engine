// Last update: 21:00 20-10-2019
// VGE.UIButton.h
// A class that represents a button in the UI
#pragma once
#ifndef VGE_UIBUTTON_H
#define VGE_UIBUTTON_H

#include <string>
#include <glm/glm.hpp>

#include "VGE.OpenGLRenderer.h"
#include "VGE.UIElement.h"
#include "VGE.TextAlignment.h"

namespace VGE
{
	class UIButton : public UIElement
	{
	public:
		UIButton(std::string text, glm::vec2 position, glm::vec2 size, glm::vec4 color, glm::vec4 textColor, TextAlignment alignment);
		~UIButton();
		void Draw(OpenGLRenderer* renderer) override;
		void SetText(std::string text);
		std::string GetText() const;
		void SetTextColor(glm::vec4 color);
		glm::vec4 GetTextColor() const;
		void SetAlignment(TextAlignment alignment);
		TextAlignment GetAlignment() const;
	private:
		std::string m_text;
		glm::vec4 m_textColor;
		TextAlignment m_alignment;
	};
}

#endif // VGE_UIBUTTON_H