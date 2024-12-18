// VGE.UIElement.h (Base class for all UI elements)

#pragma once
#ifndef VGE_UIELEMENT_H
#define VGE_UIELEMENT_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <glm/glm.hpp>

#include "VGE.OpenGLRenderer.h"

class OpenGLRenderer;

class UIElement
{
public:
	UIElement();
	virtual ~UIElement();
	virtual void Render(OpenGLRenderer& renderer) = 0;
	virtual void HandleInput(const glm::vec2& inputPosition) = 0;
	virtual void Update(float deltaTime) = 0;

	// Properties
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;

	// State
	bool IsVisible;
	bool IsEnabled;

	// Events
	std::function<void()> OnClick;
	std::function<void()> OnHover;
	std::function<void()> OnFocus;
	std::function<void()> OnBlur;
	std::function<void()> OnEnter;
	std::function<void()> OnLeave;

	// Methods
	void SetPosition(const glm::vec2& position);
	void SetSize(const glm::vec2& size);
	void SetColor(const glm::vec4& color);
	void SetVisible(bool visible);
	void SetEnabled(bool enabled);
	virtual void AddChild(std::shared_ptr<UIElement> child);
	virtual void RemoveChild(std::shared_ptr<UIElement> child);
	virtual void ClearChildren();

protected:
	// Children
	std::vector<std::shared_ptr<UIElement>> m_children;
	std::shared_ptr<UIElement> m_parent;
	std::shared_ptr<UIElement> m_focusedChild;
	std::shared_ptr<UIElement> m_hoveredChild;
	std::shared_ptr<UIElement> m_clickedChild;
	std::shared_ptr<UIElement> m_pressedChild;
	std::shared_ptr<UIElement> m_selectedChild;
	std::shared_ptr<UIElement> m_activeChild;
	std::shared_ptr<UIElement> m_disabledChild;
	std::shared_ptr<UIElement> m_visibleChild;
	std::shared_ptr<UIElement> m_hiddenChild;
	std::shared_ptr<UIElement> m_enteredChild;
	std::shared_ptr<UIElement> m_leftChild;

private:
	// Member variables
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec4 m_color;
};

#endif // VGE_UIELEMENT_H