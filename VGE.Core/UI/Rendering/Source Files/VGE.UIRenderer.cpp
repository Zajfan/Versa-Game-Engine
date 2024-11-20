#include "../Header Files/VGE.UIRenderer.h"
#include <iostream>

namespace VGE {

void UIRenderer::addButton(const UIButton& button) {
    m_buttons.push_back(button);
}

void UIRenderer::render() {
    std::cout << "Rendering UI..." << std::endl;
    for (const auto& button : m_buttons) {
        std::cout << "Button: " << button.getLabel() << std::endl;
    }
}

} // namespace VGE
