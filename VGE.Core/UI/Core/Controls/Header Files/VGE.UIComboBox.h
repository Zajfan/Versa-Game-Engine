#pragma once
#ifndef VGE_UICONTEXTMENU_H
#define VGE_UICONTEXTMENU_H

#include "VGE.UIElement.h"

namespace VGE {
	class UIContextMenu : public UIElement {
	public:
		UIContextMenu();
		virtual ~UIContextMenu();
		virtual void Render(OpenGLRenderer& renderer) override; // Override the Render method
		// Override the base class methods
		void AddChild(std::shared_ptr<UIElement> child) override;
		void RemoveChild(std::shared_ptr<UIElement> child) override;
		void ClearChildren() override;
	};
}

#endif // VGE_UICONTEXTMENU_H