#pragma once

namespace tonic::graphics
{
class RenderAPI
{
public:
    static void Initialize();
    static void SetClearColor(float r, float g, float b, float a);
    static void Clear();

    static void ActivateTexture(int t);
    static void DrawElements(int mode, int count, int type, const void *indices);
    static void DrawArray(int mode, int first, int count);
};
}