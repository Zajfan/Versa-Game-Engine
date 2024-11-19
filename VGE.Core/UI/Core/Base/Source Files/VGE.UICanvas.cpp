#include "VGE.UICanvas.h"
#include "VGE.UIElement.h"

namespace VGE {
	UICanvas::UICanvas() {
	}
	UICanvas::~UICanvas() {
	}

	void UICanvas::Render(OpenGLRenderer& renderer) {
		for (auto& element : m_children) {
			element->Render(renderer);
		}
	}

	void UICanvas::AddChild(std::shared_ptr<UIElement> child) {
		UIElement::AddChild(child); // Explicitly qualify the base class member function
	}

	void UICanvas::RemoveChild(std::shared_ptr<UIElement> child) {
		UIElement::RemoveChild(child); // Explicitly qualify the base class member function
	}

	void UICanvas::ClearChildren() {
		UIElement::ClearChildren(); // Explicitly qualify the base class member function
	}
}
