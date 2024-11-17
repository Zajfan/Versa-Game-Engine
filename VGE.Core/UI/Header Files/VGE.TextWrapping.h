#pragma once
#ifndef VGE_TEXTWRAPPING_H
#define VGE_TEXTWRAPPING_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace VGE
{
	class TextWrapping
	{
	public:
		// Wrap the text to fit within the specified width
		static std::vector<std::string> WrapText(const std::string& text, const std::string& fontName, unsigned int fontSize, float width);
		// Calculate the height of the wrapped text
		static float CalculateWrappedTextHeight(const std::vector<std::string>& lines, const std::string& fontName, unsigned int fontSize);
		// Calculate the width of the wrapped text
		static float CalculateWrappedTextWidth(const std::vector<std::string>& lines, const std::string& fontName, unsigned int fontSize);
		// Draw the wrapped text
		static void DrawWrappedText(const std::vector<std::string>& lines, const glm::vec2& position, const std::string& fontName, unsigned int fontSize, const glm::vec3& color);
	};
}

#endif // VGE_TEXTWRAPPING_H
