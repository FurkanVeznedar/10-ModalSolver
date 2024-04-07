#ifndef _SHADER_H_
#define _SHADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "glm/glm.hpp"

struct shaderProgramSource
{
	std::string vertexsource;
	std::string fragmentsource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, GLint> m_UniformLocationCache; 
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //Set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform2f(const std::string& name, float v0, float v1);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
    shaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    GLint GetUniformLocation(const std::string& name);
};

#endif _SHADER_H_