#ifndef UITEXTBOX_H
#define UITEXTBOX_H

#include "UIElement.h"
#include <string>

class UITextBox : public UIElement
{
public:
    UITextBox();

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::string Text;
    std::string PlaceholderText = "Enter text..."; // Text displayed when the text box is empty
    bool IsEditing = false; // Whether the text box is currently being edited
    int CursorPosition = 0; // Position of the text cursor

private:
    // ... (Helper functions or member variables)
    // For example:
    // - float textOffsetX = 5.0f; // Horizontal offset for the text within the box
    // - float textOffsetY = 5.0f; // Vertical offset for the text within the box
};

#endif // UITEXTBOX_H