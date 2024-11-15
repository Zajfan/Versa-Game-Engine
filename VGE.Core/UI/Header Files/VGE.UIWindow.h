#pragma once
#ifndef VGE_UIWINDOW_H
#define VGE_UIWINDOW_H

#include <string>
#include <functional>
#include <glm/glm.hpp>

#include "VGE.UIElement.h"
#include "VGE.OpenGLRenderer.h"

class UIWindow : public UIElement
{
public:
	UIWindow();
	virtual ~UIWindow();
	virtual void Render(OpenGLRenderer& renderer) override;
	virtual void HandleInput(const glm::vec2& inputPosition) override;
	virtual void Update(float deltaTime) override;

	// Methods
	void Close();
	void Drag();
	void Resize();
	
	// Properties
	std::string Title;
	bool IsOpen;
	bool IsDraggable;
	bool IsResizable;
	glm::vec2 MinSize;
	glm::vec2 MaxSize;

	// Events
	std::function<void()> OnClose;
	std::function<void()> OnDrag;
	std::function<void()> OnResize;

private:

	// ... (Helper functions or member variables)
	// For example:
	// - bool m_isDragging;
	// - glm::vec2 m_dragOffset;
	// - bool m_isResizing;
	// - glm::vec2 m_resizeOffset;
};

#endif // VGE_UIWINDOW_H