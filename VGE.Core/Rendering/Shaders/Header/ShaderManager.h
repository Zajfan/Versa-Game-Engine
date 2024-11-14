#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <iostream>
#include <string>
#include <glew.h>

class ShaderManager {
public:
    GLuint LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
	void ReloadShader(GLuint programID, const std::string& vertexPath, const std::string& fragmentPath);

private:
    std::string ReadFile(const std::string& filePath);
    void CheckCompileErrors(GLuint shader, const std::string& type);
	void CheckLinkErrors(GLuint programID);
	GLuint CompileShader(const std::string& source, GLenum shaderType);
};

#endif // SHADER_MANAGER_H
