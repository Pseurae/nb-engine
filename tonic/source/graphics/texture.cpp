#include "tonic/graphics/texture.h"
#include <GL/gl3w.h>

namespace tonic::graphics
{
Texture::Texture(int width, int height, int numChannels) :
    m_Width(width), m_Height(height), m_NumChannels(numChannels)
{
    glGenTextures(1, &m_Texture);

    glBindTexture(GL_TEXTURE_2D, m_Texture);

    int channel = m_NumChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const unsigned char *data, int width, int height, int numChannels) :
    m_Width(width), m_Height(height), m_NumChannels(numChannels)
{
    glGenTextures(1, &m_Texture);

    glBindTexture(GL_TEXTURE_2D, m_Texture);

    int channel = m_NumChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_Texture);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetWrapping(TextureWrap x, TextureWrap y) const
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetWrappingType(x));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetWrappingType(y));
    Unbind();
}

void Texture::SetFilter(TextureFilter min, TextureFilter mag) const
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetFilterType(min));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetFilterType(mag));
    Unbind();
}

void Texture::SetBorderColor(const glm::vec4 &color) const
{
    Bind();
    glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR, color.data.data);
    Unbind();
}

unsigned int Texture::GetWrappingType(TextureWrap w)
{
    switch (w)
    {
    case TextureWrap::ClampToBorder:
        return GL_CLAMP_TO_BORDER;
    case TextureWrap::ClampToEdge:
        return GL_CLAMP_TO_EDGE;
    case TextureWrap::MirroredClampToEdge:
        return GL_MIRROR_CLAMP_TO_EDGE;
    case TextureWrap::MirroredRepeat:
        return GL_MIRRORED_REPEAT;
    case TextureWrap::Repeat:
    default:
        return GL_REPEAT;
    }
}

unsigned int Texture::GetFilterType(TextureFilter f)
{
    switch (f)
    {
    case TextureFilter::Nearest:
        return GL_NEAREST;
    case TextureFilter::Linear:
    default:
        return GL_LINEAR;
    }
}
}