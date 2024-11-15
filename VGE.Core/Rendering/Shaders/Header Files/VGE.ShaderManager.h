#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <unordered_map>
#include <glad.h>
#include <glm/glm.hpp>

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    GLuint LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void ReloadShader(GLuint programID, const std::string& vertexPath, const std::string& fragmentPath);

private:
    std::string ReadFile(const std::string& filePath);
    GLuint CompileShader(const std::string& source, GLenum shaderType);
    void CheckCompileErrors(GLuint shader, const std::string& type);
    void CheckLinkErrors(GLuint program);

    std::unordered_map<GLuint, std::pair<std::string, std::string>> m_shaderPrograms;
};

#endif // SHADERMANAGER_H
