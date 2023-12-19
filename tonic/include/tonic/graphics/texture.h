#pragma once

#include <glm/vec4.hpp>

namespace tonic::graphics
{
enum class TextureWrap
{
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    MirroredClampToEdge,
    ClampToBorder
};

enum class TextureFilter
{
    Linear,
    Nearest,
    NearestMipNearest,
    LinearNipNearest,
    NearestMipLinear,
    LinearMipLinear
};

class Texture
{
public:
    Texture(int width, int height, int numChannels);
    Texture(const unsigned char *data, int width, int height, int numChannels);
    ~Texture();

    void Bind() const;
    void Unbind() const;

    void SetWrapping(TextureWrap x, TextureWrap y) const;
    void SetFilter(TextureFilter min, TextureFilter mag) const;
    void SetBorderColor(const glm::vec4 &color) const;

    inline unsigned int GetID() { return m_Texture; } 
private:
    static unsigned int GetWrappingType(TextureWrap w);
    static unsigned int GetFilterType(TextureFilter f);

    unsigned int m_Texture;
    unsigned int m_Width, m_Height, m_NumChannels;
};
}