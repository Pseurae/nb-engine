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

int Shader::GetUniformLocation(const std::string &name) const
{
    return glGetUniformLocation(m_Program, name.c_str());
}

#define DEFINE_PRIM(type, suf) \
template <> void Shader::SetUniform(const std::string &name, type i) const \
{ \
    Use(); \
    glUniform1##suf(GetUniformLocation(name.c_str()), i); TONIC_CHECK_GL_ERROR(); \
} \
template <> void Shader::SetUniform(const std::string &name, const glm::vec<1, type, glm::qualifier::defaultp> &i) const \
{ \
    Use(); \
    glUniform1##suf(GetUniformLocation(name.c_str()), i.x); TONIC_CHECK_GL_ERROR(); \
} \
template <> void Shader::SetUniform(const std::string &name, const glm::vec<2, type, glm::qualifier::defaultp> &i) const \
{ \
    Use(); \
    glUniform2##suf(GetUniformLocation(name.c_str()), i.x, i.y); TONIC_CHECK_GL_ERROR(); \
} \
template <> void Shader::SetUniform(const std::string &name, const glm::vec<3, type, glm::qualifier::defaultp> &i) const \
{ \
    Use(); \
    glUniform3##suf(GetUniformLocation(name.c_str()), i.x, i.y, i.z); TONIC_CHECK_GL_ERROR(); \
} \
template <> void Shader::SetUniform(const std::string &name, const glm::vec<4, type, glm::qualifier::defaultp> &i) const \
{ \
    Use(); \
    glUniform4##suf(GetUniformLocation(name.c_str()), i.x, i.y, i.z, i.w); TONIC_CHECK_GL_ERROR(); \
} \


#define DEFINE_MAT(d) \
template <> void Shader::SetUniform(const std::string &name, const glm::mat##d &i) const \
{ \
    Use(); \
    glUniformMatrix##d##fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(i)); TONIC_CHECK_GL_ERROR();\
} \

#include "tonic/graphics/shader_uniform.inl"

#undef DEFINE_PRIM
#undef DEFINE_MAT
}