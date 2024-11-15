// VGE.UIElement.h (Base class for all UI elements)
#pragma once
#ifndef VGE_UIELEMENT_H
#define VGE_UIELEMENT_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <glm/glm.hpp>

#include "VGE.OpenGLRenderer.h" // Include the OpenGLRenderer header

class OpenGLRenderer;

class UIElement
{
public:
	UIElement();
	virtual ~UIElement();
	virtual void Render(OpenGLRenderer& renderer) = 0;
	virtual void HandleInput(const glm::vec2& inputPosition) = 0;
	// Properties
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;
	// Events
	std::function<void()> OnClick;
	std::function<void()> OnHover;
	std::function<void()> OnLeave;
	// Methods
	void AddChild(std::shared_ptr<UIElement> child);
	void RemoveChild(std::shared_ptr<UIElement> child);
	void ClearChildren();
protected:
	std::vector<std::shared_ptr<UIElement>> m_children;
};

#endif // VGE_UIELEMENT_H


