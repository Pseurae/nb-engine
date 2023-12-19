#pragma once

#include <string>
#include <glm/mat4x4.hpp>

namespace tonic::graphics
{
class Shader
{
public:
    Shader(const std::string &vertex, const std::string &fragment);
    ~Shader();

    void Use() const;

    [[nodiscard]] int GetUniformLocation(const std::string &name) const;
    void SetUniform1i(const std::string &name, int i) const;
    void SetUniform1f(const std::string &name, float i) const;
    void SetUniformMat4(const std::string& name, const glm::mat4& mat) const;
private:
    unsigned int m_Program;
};
}