#pragma once

namespace tonic::graphics
{
void CheckGLError();
void SetClearColor(float r, float g, float b, float a);
void Clear();

void ActivateTexture(int t);
void DrawElements(int mode, int count, int type, const void *indices);
}

#ifndef TONIC_CONFIG_RELEASE
#define TONIC_CHECK_GL_ERROR() ::tonic::graphics::CheckGLError()
#else
#define TONIC_CHECK_GL_ERROR (void *)0
#endif