#include "OpenGLRenderer.h"
#include "UIManager.h"

UIManager uiManager;

OpenGLRenderer::OpenGLRenderer()
    : m_clearColor(0.0f, 0.0f, 0.0f)
{
    // Other initialization code
}

OpenGLRenderer::~OpenGLRenderer()
{
    // Cleanup code
}

void OpenGLRenderer::Initialize(void* windowHandle)
{
    // ... (Window setup and OpenGL context creation)

    // Initialize GLAD
    if (!gladLoadGL())
    {
        // Handle GLAD initialization error
        return;
    }

    // Load shaders
    m_shaderProgram = m_shaderManager.LoadShader("path/to/vertex_shader.glsl", "path/to/fragment_shader.glsl");

    // ... (Rest of your OpenGL initialization)
}

void OpenGLRenderer::Render()
{
    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the shader program
    glUseProgram(m_shaderProgram);

    // Set uniforms (example: model, view, projection matrices)
    // ... (Implement uniform setting logic here)

    // Bind the VAO
    glBindVertexArray(m_vao);

    // Draw the object (example: a rectangle)
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind the VAO
    glBindVertexArray(0);

    // Render UI elements
    for (auto& element : uiManager.GetElements())
    {
        if (element->IsVisible)
        {
            element->Render(*this);
        }
    }
}

void OpenGLRenderer::DrawText(const std::string& text, const glm::vec2& position, const std::string& fontName, unsigned int fontSize, const glm::vec3& color) {
    // Implement text rendering using OpenGL
}

void OpenGLRenderer::DrawButton(const glm::vec2& position, const glm::vec2& size, const std::string& label, const glm::vec3& color) {
    // Implement button rendering using OpenGL
}

void OpenGLRenderer::DrawCheckbox(const glm::vec2& position, bool isChecked, const std::string& label, const glm::vec3& color) {
    // Implement checkbox rendering using OpenGL
}

void OpenGLRenderer::DrawSlider(const glm::vec2& position, float minValue, float maxValue, float currentValue, const glm::vec3& color) {
    // Implement slider rendering using OpenGL
}

// ... (Implementations for other methods: ClearScreen, DrawRectangle, etc.)
