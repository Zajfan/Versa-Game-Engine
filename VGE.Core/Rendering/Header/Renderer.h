// File: Renderer.h
#pragma once
#include <glm/glm.hpp>
#include <string>

class Renderer {
public:
    virtual void Initialize(void* windowHandle) = 0;
    virtual void Render() = 0;
    virtual float GetTextHeight(const std::string& fontName, unsigned int fontSize) = 0;
    virtual float GetTextWidth(const std::string& text, const std::string& fontName, unsigned int fontSize) = 0;
    virtual void ClearScreen(const glm::vec3& color) = 0;
    virtual void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) = 0;
    virtual void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color) = 0;
    virtual void DrawText(const std::string& text, const glm::vec2& position, const std::string& fontName, unsigned int fontSize, const glm::vec3& color) = 0;
    virtual void DrawSprite(const std::string& texturePath, const glm::vec2& position, const glm::vec2& size) = 0;
    virtual void DrawCircle(const glm::vec2& center, float radius, const glm::vec3& color) = 0;

    // ... other common rendering methods
};
