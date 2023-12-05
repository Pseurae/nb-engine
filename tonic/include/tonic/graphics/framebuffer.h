#pragma once

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
private:
    unsigned int m_FBO, m_Width, m_Height;
    Texture m_Texture;
};
}