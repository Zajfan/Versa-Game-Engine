#pragma once
#ifndef VGE_UISCROLLBAR_H
#define VGE_UISCROLLBAR_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory>

#include "VGE.UIElement.h"

class UIScrollbar : public UIElement
{
public:
	UIScrollbar(const std::string& name);
	~UIScrollbar();
	// Properties
	float Value;
	float MinValue;
	float MaxValue;
	float StepSize;
	// Methods
	void SetValue(float value);
	float GetValue() const;
	void SetMinValue(float minValue);
	float GetMinValue() const;
	void SetMaxValue(float maxValue);
	float GetMaxValue() const;
	void SetStepSize(float stepSize);
	float GetStepSize() const;
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

#endif // VGE_UISCROLLBAR_H
