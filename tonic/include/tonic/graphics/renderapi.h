#pragma once

#include "tonic/graphics/framebuffer.h"
#include <stack>
#include <memory>

namespace tonic::graphics
{
class RenderAPI final
{
public:
    static void Initialize();
    static void SetClearColor(float r, float g, float b, float a);
    static void Clear();

    static void BindDefaultFramebuffer();
    static void SetViewport(int x, int y, int w, int h);
    static void ActivateTexture(int t);
    static void DrawElements(int mode, int count, int type, const void *indices);
    static void DrawArray(int mode, int first, int count);

    static void PushFramebuffer(std::shared_ptr<FrameBuffer> fbo);
    static void PopFramebuffer();
private:
    static std::stack<std::shared_ptr<FrameBuffer>> m_FramebufferStack;
};
}