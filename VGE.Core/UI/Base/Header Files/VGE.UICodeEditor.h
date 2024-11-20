#pragma once
#ifndef VGE_UICODEEDITOR_H
#define VGE_UICODEEDITOR_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory>

#include "VGE.UIElement.h"
#include "VGE.UIText.h"
#include "VGE.UIButton.h"
#include "VGE.UIScrollbar.h"

class UICodeEditor : public UIElement
{
public:
	UICodeEditor(const std::string& name);
	~UICodeEditor();
	// Properties
	std::string Code;
	std::string Language;
	std::string Theme;
	std::string Font;
	int FontSize = 12;
	// Methods
	void LoadFile(const std::string& filePath);
	void SaveFile(const std::string& filePath);
	void SetCode(const std::string& code);
	std::string GetCode() const;
	void SetLanguage(const std::string& language);
	std::string GetLanguage() const;
	void SetTheme(const std::string& theme);
	std::string GetTheme() const;
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
private:
	UIText* TextEditor;
	UIScrollbar* VerticalScrollbar;
	UIScrollbar* HorizontalScrollbar;
	UIButton* SaveButton;
	UIButton* LoadButton;
};

#endif // VGE_UICODEEDITOR_H
