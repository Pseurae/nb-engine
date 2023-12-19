#include "tonic/graphics/texture.h"
#include "tonic/graphics/helpers.h"
#include <GL/gl3w.h>

namespace tonic::graphics
{
Texture::Texture(int width, int height, int numChannels) :
    m_Width(width), m_Height(height), m_NumChannels(numChannels)
{
    glGenTextures(1, &m_Texture); TONIC_CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, m_Texture); TONIC_CHECK_GL_ERROR();

    int channel = m_NumChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, nullptr); TONIC_CHECK_GL_ERROR();
    glGenerateMipmap(GL_TEXTURE_2D); TONIC_CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, 0); TONIC_CHECK_GL_ERROR();
}

Texture::Texture(const unsigned char *data, int width, int height, int numChannels) :
    m_Width(width), m_Height(height), m_NumChannels(numChannels)
{
    glGenTextures(1, &m_Texture); TONIC_CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, m_Texture); TONIC_CHECK_GL_ERROR();

    int channel = m_NumChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data); TONIC_CHECK_GL_ERROR();
    glGenerateMipmap(GL_TEXTURE_2D); TONIC_CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, 0); TONIC_CHECK_GL_ERROR();
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_Texture); TONIC_CHECK_GL_ERROR();
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_Texture); TONIC_CHECK_GL_ERROR();
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0); TONIC_CHECK_GL_ERROR();
}

void Texture::SetWrapping(TextureWrap x, TextureWrap y) const
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetWrappingType(x)); TONIC_CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetWrappingType(y)); TONIC_CHECK_GL_ERROR();
    Unbind();
}

void Texture::SetFilter(TextureFilter min, TextureFilter mag) const
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetFilterType(min)); TONIC_CHECK_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetFilterType(mag)); TONIC_CHECK_GL_ERROR();
    Unbind();
}

void Texture::SetBorderColor(const glm::vec4 &color) const
{
    Bind();
    glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR, color.data.data); TONIC_CHECK_GL_ERROR();
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
    [[unlikely]] default:
        return GL_REPEAT;
    }
}

unsigned int Texture::GetFilterType(TextureFilter f)
{
    switch (f)
    {
    case TextureFilter::Nearest:
        return GL_NEAREST;
    case TextureFilter::NearestMipNearest:
        return GL_NEAREST_MIPMAP_NEAREST;
    case TextureFilter::LinearNipNearest:
        return GL_LINEAR_MIPMAP_NEAREST;
    case TextureFilter::NearestMipLinear:
        return GL_NEAREST_MIPMAP_LINEAR;
    case TextureFilter::LinearMipLinear:
        return GL_LINEAR_MIPMAP_LINEAR;
    case TextureFilter::Linear:
    [[unlikely]] default:
        return GL_LINEAR;
    }
}
}