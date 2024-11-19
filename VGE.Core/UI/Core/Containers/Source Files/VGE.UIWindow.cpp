#include "VGE.UIWindow.h"
#include "VGE.OpenGLRenderer.h"

UIWindow::UIWindow(const std::string& title, const glm::vec2& position, const glm::vec2& size)
    : UIElement(),
    Title(title),
    Position(position),
    Size(size),
	Color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	TitleColor(glm::vec4(1.0f)),
	BorderColor(glm::vec4(0.5f)),
	BorderWidth(1.0f),
	BorderRadius(0.0f),
	ShadowColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)),
	ShadowOffset(glm::vec2(2.0f)),
	ShadowBlur(5.0f),
	TitleBarHeight(20.0f),
	TitleFontSize(14.0f),
	ContentPadding(8.0f),
	ContentMargin(8.0f)
{
	// Initialize the window state
	m_windowState = 0;
	// Initialize the window actions
	for (int i = 0; i < (int)WindowAction::Count; i++) {
		m_windowActions[i] = nullptr;
	}
}

void UIWindow::SetState(WindowState state, bool value) {
    if (value) {
        m_windowState |= static_cast<unsigned int>(state);
    }
    else {
        m_windowState &= ~static_cast<unsigned int>(state);
    }
}

bool UIWindow::HasState(WindowState state) const {
    return (m_windowState & static_cast<unsigned int>(state)) != 0;
}

void UIWindow::PerformAction(WindowAction action) {
    if (static_cast<int>(action) < (int)WindowAction::Count && m_windowActions[static_cast<int>(action)]) {
        m_windowActions[static_cast<int>(action)]();
    }
}

void UIWindow::SetAction(WindowAction action, std::function<void()> callback) {
    if (static_cast<int>(action) < (int)WindowAction::Count) {
        m_windowActions[static_cast<int>(action)] = callback;
    }
}

// ... (Implement other UIWindow functions: Render, Update, HandleInput, etc.) ...
