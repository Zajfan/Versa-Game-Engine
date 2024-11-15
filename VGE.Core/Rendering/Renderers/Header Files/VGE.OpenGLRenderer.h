#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Renderer.h"
#include "ShaderManager.h"
#include <glad.h>
#include <glm/glm.hpp>

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    void Initialize(void* windowHandle) override;
    void Render() override;
	float GetTextHeight(const std::string& fontName, unsigned int fontSize) override;
	float GetTextWidth(const std::string& text, const std::string& fontName, unsigned int fontSize) override;
    void ClearScreen(const glm::vec3& color) override;
    void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) override;
    void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color) override;
    // Ensure the DrawText declaration matches the one in Renderer.h
    void DrawText(const std::string& text, const glm::vec2& position, const std::string& fontName, unsigned int fontSize, const glm::vec3& color) override;

    // ... (Add other drawing methods for sprites, text, etc.)

private:
    // Helper functions
    void CreateShaders();
    void CreateQuadVAO();

    // Member variables
    GLuint m_shaderProgram;
    GLuint m_vao, m_vbo; // Vertex Array Object and Vertex Buffer Object
    glm::vec3 m_clearColor;
    ShaderManager m_shaderManager; // Declare m_shaderManager
    // ... (Other member variables as needed, e.g., for textures, framebuffers, etc.)
};

#endif // OPENGLRENDERER_H