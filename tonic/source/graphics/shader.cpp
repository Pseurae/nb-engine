#include "tonic/graphics/shader.h"
#include "tonic/graphics/helpers.h"
#include "tonic/log.h"

#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace tonic::graphics
{
Shader::Shader(const std::string &vertex, const std::string &fragment)
{
    const char *vertexSource = vertex.c_str();
    const char *fragmentSource = fragment.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); TONIC_CHECK_GL_ERROR();
    glShaderSource(vertexShader, 1, &vertexSource, NULL); TONIC_CHECK_GL_ERROR();
    glCompileShader(vertexShader); TONIC_CHECK_GL_ERROR();
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); TONIC_CHECK_GL_ERROR();
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        TONIC_ERROR("Vertex shader compilation error:\n%s", infoLog);
        TONIC_BREAK();
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); TONIC_CHECK_GL_ERROR();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL); TONIC_CHECK_GL_ERROR();
    glCompileShader(fragmentShader); TONIC_CHECK_GL_ERROR();
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); TONIC_CHECK_GL_ERROR();
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        TONIC_ERROR("Fragment shader compilation error:\n%s", infoLog);
        TONIC_BREAK();
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram(); TONIC_CHECK_GL_ERROR();
    glAttachShader(shaderProgram, vertexShader); TONIC_CHECK_GL_ERROR();
    glAttachShader(shaderProgram, fragmentShader); TONIC_CHECK_GL_ERROR();
    glLinkProgram(shaderProgram); TONIC_CHECK_GL_ERROR();
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); TONIC_CHECK_GL_ERROR();
    if (!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        TONIC_ERROR("Shader linking error:\n%s", infoLog);
        TONIC_BREAK();
    }
    glDeleteShader(vertexShader); TONIC_CHECK_GL_ERROR();
    glDeleteShader(fragmentShader); TONIC_CHECK_GL_ERROR();

    m_Program = shaderProgram;
}

Shader::~Shader()
{
    glDeleteProgram(m_Program); TONIC_CHECK_GL_ERROR();
}

void Shader::Use() const
{
    glUseProgram(m_Program); TONIC_CHECK_GL_ERROR();
}

void Shader::SetUniform1i(const std::string &name, int i) const
{
    Use();
    glUniform1i(glGetUniformLocation(m_Program, name.c_str()), i); TONIC_CHECK_GL_ERROR();
}

void Shader::SetUniform1f(const std::string &name, float i) const
{
    Use();
    glUniform1f(glGetUniformLocation(m_Program, name.c_str()), i); TONIC_CHECK_GL_ERROR();
}
void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat) const
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)); TONIC_CHECK_GL_ERROR();
}
}