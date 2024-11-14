#ifndef UIMENUBAR_H
#define UIMENUBAR_H

#include "UIElement.h"
#include <vector>
#include <string>
#include <functional>

class UIMenuItem;

class UIMenuBar : public UIElement
{
public:
    UIMenuBar();

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

    void AddMenu(const std::string& name);
    UIMenuItem* AddMenuItem(const std::string& menuName, const std::string& itemName, std::function<void()> callback);

private:
    // ... (Helper functions or member variables)
    std::vector<std::unique_ptr<UIMenuItem>> menus_;
};

class UIMenuItem : public UIElement
{
public:
    UIMenuItem(const std::string& name, std::function<void()> callback);

    void Render(OpenGLRenderer& renderer) override;
    bool HandleInput(const InputEvent& event) override;

private:
    std::string name_;
    std::function<void()> callback_;
    // ... other properties like submenu items
};

#endif // UIMENUBAR_H