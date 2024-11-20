#pragma once
#ifndef VGE_UITREEVIEWNODE_H
#define VGE_UITREEVIEWNODE_H

#include "VGE.UIElement.h"

namespace VGE {
	class UITreeViewNode : public UIElement {
	public:
		UITreeViewNode();
		virtual ~UITreeViewNode();
		virtual void Render(OpenGLRenderer& renderer) override; // Override the Render method
		// Override the base class methods
		void AddChild(std::shared_ptr<UIElement> child) override;
		void RemoveChild(std::shared_ptr<UIElement> child) override;
		void ClearChildren() override;
	};
}

#endif // VGE_UITREEVIEWNODE_H