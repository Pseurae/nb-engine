#include "tonic/graphics/renderapi.h"
#include "tonic/graphics/helpers.h"
#include "tonic/engine.h"
#include <GL/gl3w.h>
#include "tonic/log.h"

namespace tonic::graphics
{
std::stack<std::shared_ptr<FrameBuffer>> RenderAPI::m_FramebufferStack;

void RenderAPI::Initialize()
{
    glEnable(GL_BLEND); TONIC_CHECK_GL_ERROR();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); TONIC_CHECK_GL_ERROR();

    glEnable(GL_LINE_SMOOTH); TONIC_CHECK_GL_ERROR();
}

void RenderAPI::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a); TONIC_CHECK_GL_ERROR();
}

void RenderAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); TONIC_CHECK_GL_ERROR();
}

void RenderAPI::ActivateTexture(int t)
{
    glActiveTexture(GL_TEXTURE0 + t); TONIC_CHECK_GL_ERROR();
}

void RenderAPI::DrawElements(int mode, int count, int type, const void *indices)
{
    glDrawElements(mode, count, type, indices); TONIC_CHECK_GL_ERROR();
}

void RenderAPI::DrawArray(int mode, int first, int count)
{
    glDrawArrays(mode, first, count); TONIC_CHECK_GL_ERROR();
}

void RenderAPI::PushFramebuffer(std::shared_ptr<FrameBuffer> fbo)
{
    fbo->Bind();
    m_FramebufferStack.push(fbo);

    const auto color = fbo->GetClearColor();
    const auto size = fbo->GetSize();

    SetClearColor(color.r, color.g, color.b, color.a);
    Clear();

    glViewport(0, 0, size.x, size.y);
}

void RenderAPI::PopFramebuffer()
{
    TONIC_ASSERT(!m_FramebufferStack.empty(), "Framebuffer stack is empty.");
    m_FramebufferStack.pop();

    if (m_FramebufferStack.empty())
    {
        const auto size = tonic::Engine::Instance().GetWindow().GetFramebufferSize();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, size.x, size.y);
    }
    else
    {
        const auto size = m_FramebufferStack.top()->GetSize();
        m_FramebufferStack.top()->Bind();
        glViewport(0, 0, size.x, size.y);
    }
}
}