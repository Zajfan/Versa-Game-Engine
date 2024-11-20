#pragma once

#include "../../Controls/Header Files/VGE.UIButton.h"
#include <vector>

namespace VGE {

class UIRenderer {
public:
    void addButton(const UIButton& button);
    void render();

private:
    std::vector<UIButton> m_buttons;
};

} // namespace VGE
