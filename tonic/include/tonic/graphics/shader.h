#pragma once

#include <string>

#include <glm/glm.hpp>
#include <vector>

namespace tonic::graphics
{
// TODO: Should I have different functions for all possible uniform types, or just have a single template function?
// Would be a no-brainer, but I don't want to include the GL headers here unless necessary.
// Maybe, X Macros would work here?

class Shader
{
public:
    Shader(const std::string &vertex, const std::string &fragment);
    ~Shader();

    void Use() const;

    [[nodiscard]] int GetUniformLocation(const std::string &name) const;

    // SetUniform for primitive types
    template<typename T>
    void SetUniform(const std::string &name, T i) const
    {
        []<bool flag = false>{ static_assert(flag, "Type not supported"); }();
    }

    // SetUniform for vector types
    template<glm::length_t L, typename T, glm::qualifier Q>
    void SetUniform(const std::string &name, const glm::vec<L, T, Q> &i) const
    {
        []<bool flag = false>{ static_assert(flag, "Type not supported"); }();
    }

    // SetUniform for matrix types
    template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
    void SetUniform(const std::string &name, const glm::mat<C, R, T, Q> &i) const
    {
        []<bool flag = false>{ static_assert(flag, "Type not supported"); }();
    }

    // Next time.
    // SetUniform for primitive arrays
    template<typename T>
    void SetUniform(const std::string &name, const std::vector<T> &i) const
    {
        []<bool flag = false>{ static_assert(flag, "Type not supported"); }();
    }

    // SetUniform for vector arrays
    template<glm::length_t L, typename T, glm::qualifier Q>
    void SetUniform(const std::string &name, const std::vector<glm::vec<L, T, Q>> &i) const
    {
        []<bool flag = false>{ static_assert(flag, "Type not supported"); }();
    }

    // SetUniform for matrix arrays
    template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
    void SetUniform(const std::string &name, const std::vector<glm::mat<C, R, T, Q>> &i) const
    {
        []<bool flag = false>{ static_assert(flag, "Type not supported"); }();
    }

#define DEFINE_PRIM(type, suf) \
template <> void SetUniform(const std::string &name, type i) const; \
template <> void SetUniform(const std::string &name, const glm::vec<1, type, glm::qualifier::defaultp> &i) const; \
template <> void SetUniform(const std::string &name, const glm::vec<2, type, glm::qualifier::defaultp> &i) const; \
template <> void SetUniform(const std::string &name, const glm::vec<3, type, glm::qualifier::defaultp> &i) const; \
template <> void SetUniform(const std::string &name, const glm::vec<4, type, glm::qualifier::defaultp> &i) const; \

#define DEFINE_MAT(d) \
template <> void SetUniform(const std::string &name, const glm::mat##d &i) const; \

#include "tonic/graphics/shader_uniform.inl"

#undef DEFINE_PRIM
#undef DEFINE_MAT
private:
    unsigned int m_Program;
};
}