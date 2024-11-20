#pragma once
#ifndef VGE_UITEXT_H
#define VGE_UITEXT_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory>

#include "VGE.UIElement.h"

class UIText : public UIElement
{
public:
	UIText(const std::string& name);
	~UIText();
	// Properties
	std::string Text;
	std::string Font;
	int FontSize = 12;
	// Methods
	void SetText(const std::string& text);
	std::string GetText() const;
	void SetFont(const std::string& font);
	std::string GetFont() const;
	void SetFontSize(int fontSize);
	int GetFontSize() const;
	// UI Interaction
	void OnMouseClick(int x, int y) override;
	void OnMouseDoubleClick(int x, int y) override;
	void OnMouseHover(int x, int y) override;
	void OnMouseLeave() override;
	void OnKeyPress(char key) override;
	void OnTextEntry(const std::string& text) override;
	// Rendering
	void Render() override;
};

#endif // VGE_UITEXT_H
