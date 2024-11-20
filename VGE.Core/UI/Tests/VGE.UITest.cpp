#include "../Controls/Header Files/VGE.UIButton.h"
#include "../Rendering/Header Files/VGE.UIRenderer.h"
#include <iostream>

int main() {
    VGE::UIButton button1("Play");
    VGE::UIButton button2("Settings");

    button1.setOnClick([]() {
        std::cout << "Play button clicked!" << std::endl;
    });

    button2.setOnClick([]() {
        std::cout << "Settings button clicked!" << std::endl;
    });

    VGE::UIRenderer renderer;
    renderer.addButton(button1);
    renderer.addButton(button2);

    std::cout << "Simulating button clicks..." << std::endl;
    button1.click();
    button2.click();

    std::cout << "Rendering UI..." << std::endl;
    renderer.render();

    return 0;
}
