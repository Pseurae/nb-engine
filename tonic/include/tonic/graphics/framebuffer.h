#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "tonic/graphics/texture.h"

namespace tonic::graphics
{
class FrameBuffer
{
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    inline auto &GetTexture() { return m_Texture; }

    void Bind() const;
    void Unbind() const;

    inline glm::ivec2 GetSize() const { return m_Size; }
    inline void SetClearColor(const glm::vec4 &color) { m_ClearColor = color; }
    inline const auto GetClearColor() const { return m_ClearColor; }
private:
    unsigned int m_FBO;
    glm::ivec2 m_Size;
    glm::vec4 m_ClearColor;
    Texture m_Texture;
};
}