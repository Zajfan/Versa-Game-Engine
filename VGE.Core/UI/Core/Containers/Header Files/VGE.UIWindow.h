#pragma once
#ifndef VGE_UIWINDOW_H
#define VGE_UIWINDOW_H

#include <string>
#include <functional>
#include <glm/glm.hpp>
#include <vector>

#include "VGE.UIElement.h"
#include "VGE.OpenGLRenderer.h"

enum class WindowState {
    // ... (your window states) ...
};

enum class WindowAction {
    Close,
    Minimize,
    Maximize,
    Restore,
    Resize,
    Move,
    Click,
    Hover,
    Focus,
    Blur,
    Enter,
    Leave,
    // Add more actions as needed
    Count, // Add this member to represent the count of actions
};

class UIWindow : public UIElement {
public:
    UIWindow(const std::string& title = "Window",
        const glm::vec2& position = glm::vec2(0.0f),
        const glm::vec2& size = glm::vec2(200.0f, 150.0f));
    // ... rest of the class definition ...

    // State management
    void SetState(WindowState state, bool value = true);
    bool HasState(WindowState state) const;

    // Action handling
    void PerformAction(WindowAction action);
    void SetAction(WindowAction action, std::function<void()> callback);

    // Properties
    std::string Title = "Window";
    glm::vec2 Position = glm::vec2(0.0f);
    glm::vec2 Size = glm::vec2(200.0f, 150.0f);
    glm::vec4 Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // Appearance
    glm::vec4 TitleColor = glm::vec4(1.0f); // White
    glm::vec4 BorderColor = glm::vec4(0.5f); // Gray
    float BorderWidth = 1.0f;
    float BorderRadius = 0.0f;

    glm::vec4 ShadowColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.5f);
    glm::vec2 ShadowOffset = glm::vec2(2.0f);
    float ShadowBlur = 5.0f;

    // Title bar 
    float TitleBarHeight = 20.0f;
    float TitleFontSize = 14.0f;

    // Content
    float ContentPadding = 8.0f;
    float ContentMargin = 8.0f;

    // ... other essential properties ...

private:
    unsigned int m_windowState = 0;
    std::vector<std::function<void()>> m_windowActions = std::vector<std::function<void()>>((int)WindowAction::Count, nullptr);

    // ... (helper functions and variables) ...
};

#endif // VGE_UIWINDOW_H
