#pragma once
#ifndef VGE_UITEXTAREA_H
#define VGE_UITEXTAREA_H

#include "VGE.UIElement.h"
#include "VGE.UIText.h"
#include "VGE.UIScrollBar.h"

namespace VGE
{
	class UITextArea : public UIElement
	{
	public:
		UITextArea();
		virtual ~UITextArea();
		void SetText(const std::string& text);
		void SetTextSize(unsigned int size);
		void SetTextColor(const glm::vec4& color);
		void SetTextAlignment(UIAlignment alignment);
		void SetTextPadding(const glm::vec4& padding);
		void SetTextOffset(const glm::vec2& offset);
		void SetTextWrap(bool wrap);
		void SetTextOverflow(UIOverflow overflow);
		void SetTextFont(const std::string& font);
		void SetTextLineSpacing(float spacing);
		void SetTextLetterSpacing(float spacing);
		void SetTextWordSpacing(float spacing);
		void SetTextLineHeight(float height);
		void SetTextMaxLines(unsigned int lines);
		void SetTextMaxWidth(float width);
		void SetTextMaxHeight(float height);
		void SetTextMinWidth(float width);
		void SetTextMinHeight(float height);
		void SetTextShadow(const glm::vec4& color, const glm::vec2& offset, float blur);
		void SetTextOutline(const glm::vec4& color, float thickness);
		void SetTextUnderline(const glm::vec4& color, float thickness);
		void SetTextStrikeout(const glm::vec4& color, float thickness);
		void SetTextLink(const std::string& link);
		void SetTextLinkColor(const glm::vec4& color);
		void SetTextLinkHoverColor(const glm::vec4& color);
		void SetTextLinkActiveColor(const glm::vec4& color);
		void SetTextLinkVisitedColor(const glm::vec4& color);
		void SetTextLinkUnderline(const glm::vec4& color, float thickness);
		void SetTextLinkHoverUnderline(const glm::vec4& color, float thickness);
		void SetTextLinkActiveUnderline(const glm::vec4& color, float thickness);
		void SetTextLinkVisitedUnderline(const glm::vec4& color, float thickness);
		void SetTextLinkCallback(const std::function<void(const std::string&)>& callback);
		void SetTextSelectionColor(const glm::vec4& color);
		void SetTextSelectionBackground(const glm::vec4& color);
		void SetTextSelectionPadding(const glm::vec4& padding);
		void SetTextSelectionOffset(const glm::vec2& offset);
		void SetTextSelectionCallback(const std::function<void(const std::string&)>& callback);
		void SetTextSelectionStart(unsigned int start);
		void SetTextSelectionEnd(unsigned int end);
		void SetTextSelection(const glm::vec2& start, const glm::vec2& end);
		void SetTextSelection(const glm::vec2& start, unsigned int length);
	};
}



#endif // VGE_UITEXTAREA_H
