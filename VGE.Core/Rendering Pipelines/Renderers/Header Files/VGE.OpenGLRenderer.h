#ifndef VGECORE_OPENGLRENDERER_H
#define VGECORE_OPENGLRENDERER_H

#include "Renderer.h"
#include "VGE.ShaderManager.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

	// Renderer methods
    void Initialize(void* windowHandle) override;
    void Render() override;
	float GetTextHeight(const std::string& fontName, unsigned int fontSize) override;
	float GetTextWidth(const std::string& text, const std::string& fontName, unsigned int fontSize) override;
    void ClearScreen(const glm::vec3& color) override;
    void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) override;
    void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color) override;
    // Ensure the DrawText declaration matches the one in Renderer.h
    void DrawText(const std::string& text, const glm::vec2& position, const std::string& fontName, unsigned int fontSize, const glm::vec3& color) override;
	void DrawSprite(const std::string& texturePath, const glm::vec2& position, const glm::vec2& size) override;
	void SetViewportSize(int width, int height) override;
	void SetFont(const std::string& fontPath) override;
    void DrawButton(const glm::vec2& position, const glm::vec2& size, const std::string& label, const glm::vec3& color);
    void DrawCheckbox(const glm::vec2& position, bool isChecked, const std::string& label, const glm::vec3& color);
    void DrawSlider(const glm::vec2& position, float minValue, float maxValue, float currentValue, const glm::vec3& color);
	// ... (Add other rendering methods as needed)
    // ... (Add other drawing methods for sprites, text, etc.)

private:
    // Helper functions
    void CreateShaders();
    void CreateQuadVAO();
	void CreateQuadVBO();
	// ... (Add other helper functions as needed)

    // Member variables
    GLuint m_shaderProgram;
	// Shader program ID
    GLuint m_vao, m_vbo; // Vertex Array Object and Vertex Buffer Object
    glm::vec3 m_clearColor;
    ShaderManager m_shaderManager; // Declare m_shaderManager
    // ... (Other member variables as needed, e.g., for textures, framebuffers, etc.)
};

#endif // VGECORE_OPENGLRENDERER_H