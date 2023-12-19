#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "tonic/graphics/texture.h"

namespace tonic::graphics
{
// TODO: Complete the FBO class. (Renderbuffer, Stencils, etc...)
class FrameBuffer
{
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    [[nodiscard]] inline auto &GetTexture() const { return m_Texture; }

    void Bind() const;
    void Unbind() const;

    [[nodiscard]] inline glm::ivec2 GetSize() const { return m_Size; }
    [[nodiscard]] inline void SetClearColor(const glm::vec4 &color) { m_ClearColor = color; }
    [[nodiscard]] inline const auto GetClearColor() const { return m_ClearColor; }
private:
    unsigned int m_FBO;
    glm::ivec2 m_Size;
    glm::vec4 m_ClearColor;
    Texture m_Texture;
};
}