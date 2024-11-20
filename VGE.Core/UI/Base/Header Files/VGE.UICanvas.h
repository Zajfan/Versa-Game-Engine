#pragma once
#ifndef VGE_UICANVAS_H
#define VGE_UICANVAS_H

#include "VGE.UIElement.h"

namespace VGE {
	class UICanvas : public UIElement {
	public:
		UICanvas();
		virtual ~UICanvas();
		virtual void Render(OpenGLRenderer& renderer) override; // Override the Render method

		// Override the base class methods
		void AddChild(std::shared_ptr<UIElement> child) override;
		void RemoveChild(std::shared_ptr<UIElement> child) override;
		void ClearChildren() override;
	};
}

#endif // VGE_UICANVAS_H