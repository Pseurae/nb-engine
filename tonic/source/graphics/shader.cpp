#include "tonic/graphics/shader.h"

#include <GL/gl3w.h>

namespace tonic::graphics
{
Shader::Shader(const std::string &vertex, const std::string &fragment)
{
    const char *vertexSource = vertex.c_str();
    const char *fragmentSource = fragment.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_Program = shaderProgram;
}

Shader::~Shader()
{
    glDeleteProgram(m_Program);
}

void Shader::Use() const
{
    glUseProgram(m_Program);
}

void Shader::SetUniform1i(const std::string &name, int i) const
{
    Use();
    glUniform1i(glGetUniformLocation(m_Program, name.c_str()), i);
}

void Shader::SetUniform1f(const std::string &name, float i) const
{
    Use();
    glUniform1f(glGetUniformLocation(m_Program, name.c_str()), i);
}
}