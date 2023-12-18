#include "tonic/graphics/renderapi.h"
#include "tonic/graphics/helpers.h"
#include <GL/gl3w.h>

namespace tonic::graphics
{
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
}