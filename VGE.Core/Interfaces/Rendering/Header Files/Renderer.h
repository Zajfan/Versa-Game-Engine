// File: Renderer.h
#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Renderer {
public:
	// Renderer methods
    virtual void Initialize(void* windowHandle) = 0;
    virtual void Render() = 0;
	virtual void Shutdown() = 0;
	virtual void SetViewportSize(int width, int height) = 0;
	virtual void SetFont(const std::string& fontPath) = 0;
    virtual float GetTextHeight(const std::string& fontName, unsigned int fontSize) = 0;
    virtual float GetTextWidth(const std::string& text, const std::string& fontName, unsigned int fontSize) = 0;
    virtual void ClearScreen(const glm::vec3& color) = 0;

	// Common rendering methods
    virtual ~Renderer() = default;
    virtual void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) = 0;
    virtual void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color) = 0;
    virtual void DrawText(const std::string& text, const glm::vec2& position, const std::string& fontName, unsigned int fontSize, const glm::vec3& color) = 0;
    virtual void DrawSprite(const std::string& texturePath, const glm::vec2& position, const glm::vec2& size) = 0;
    virtual void DrawCircle(const glm::vec2& center, float radius, const glm::vec3& color) = 0;
	virtual void DrawTriangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec3& color) = 0;
	virtual void DrawEllipse(const glm::vec2& center, float radiusX, float radiusY, const glm::vec3& color) = 0;
	virtual void DrawPolygon(const std::vector<glm::vec2>& points, const glm::vec3& color) = 0;
	virtual void DrawPolyline(const std::vector<glm::vec2>& points, const glm::vec3& color) = 0;
	virtual void DrawArc(const glm::vec2& center, float radius, float startAngle, float endAngle, const glm::vec3& color) = 0;
	virtual void DrawBezierCurve(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4, const glm::vec3& color) = 0;
	virtual void DrawQuadraticCurve(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec3& color) = 0;
	virtual void DrawTexturedRectangle(const std::string& texturePath, const glm::vec2& position, const glm::vec2& size) = 0;
};

#endif // RENDERER_H