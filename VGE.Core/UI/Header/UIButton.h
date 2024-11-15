// UIButton.h (Example UI element class)

#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UIElement.h"

class UIButton : public UIElement
{
public:
    UIButton(const std::string& text);

	void Update(float deltaTime) override;
    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::string Text;
	glm::vec3 TextColor = glm::vec3(0.0f, 0.0f, 0.0f); // Black by default
	glm::vec3 HoverColor = glm::vec3(0.5f, 0.5f, 0.5f); // Gray by default
	glm::vec3 PressedColor = glm::vec3(0.3f, 0.3f, 0.3f); // Dark gray by default

private:
    // ... (Helper functions or member variables)

	bool m_IsHovered = false;
	bool m_IsPressed = false;
};

#endif // UIBUTTON_H