#pragma once

#include <string>

namespace tonic::graphics
{
class Shader
{
public:
    Shader(const std::string &vertex, const std::string &fragment);
    ~Shader();

    void Use() const;
    void SetUniform1i(const std::string &name, int i) const;
    void SetUniform1f(const std::string &name, float i) const;
private:
    unsigned int m_Program;
};
}