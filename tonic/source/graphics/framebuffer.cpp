#include "tonic/graphics/framebuffer.h"
#include "tonic/graphics/helpers.h"
#include <GL/gl3w.h>

namespace tonic::graphics
{
FrameBuffer::FrameBuffer(int width, int height) : m_Width(width), m_Height(height), m_Texture(width, height, 4)
{
    glGenFramebuffers(1, &m_FBO); TONIC_CHECK_GL_ERROR();
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); TONIC_CHECK_GL_ERROR();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture.GetID(), 0); TONIC_CHECK_GL_ERROR();
    glBindFramebuffer(GL_FRAMEBUFFER, 0); TONIC_CHECK_GL_ERROR();
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_FBO); TONIC_CHECK_GL_ERROR();
}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); TONIC_CHECK_GL_ERROR();
}

void FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0); TONIC_CHECK_GL_ERROR();
}
}