#include "../Header Files/VGE.UIContextMenu.h"
#include <iostream>

namespace VGE {

UIContextMenu::UIContextMenu() {
    // Initialization code here
}

UIContextMenu::~UIContextMenu() {
    // Cleanup code here
}

void UIContextMenu::Render(OpenGLRenderer& renderer) {
    // Render the context menu using OpenGL
    std::cout << "Rendering UIContextMenu" << std::endl;
    // Add OpenGL rendering code here
    // Render the context menu using OpenGL
    // Iterate over children and render each
    for (const auto& child : m_children) {
        child->Render(renderer);
    }
}

void UIContextMenu::AddChild(std::shared_ptr<UIElement> child) {
    // Add a child element to the context menu
    std::cout << "Adding child to UIContextMenu" << std::endl;
    // Add logic to store the child
}

void UIContextMenu::RemoveChild(std::shared_ptr<UIElement> child) {
    // Remove a child element from the context menu
    std::cout << "Removing child from UIContextMenu" << std::endl;
    // Add logic to remove the child
}

void UIContextMenu::ClearChildren() {
    // Clear all child elements from the context menu
    std::cout << "Clearing children from UIContextMenu" << std::endl;
    // Add logic to clear all children
}

} // namespace VGE
