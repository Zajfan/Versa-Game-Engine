#ifndef UILIST_H
#define UILIST_H

#include "UIElement.h"
#include <vector>
#include <string>

class UIList : public UIElement
{
public:
    UIList();

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    // Properties
    std::vector<std::string> Items;
    int SelectedItemIndex = -1; // -1 indicates no item is selected

private:
    // ... (Helper functions or member variables)
    // For example:
    // - float itemHeight = 20.0f; // Height of each item in the list
    // - int scrollOffset = 0; // To handle scrolling if the list exceeds the visible area
};

#endif // UILIST_H