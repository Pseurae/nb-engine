#pragma once

namespace tonic::graphics
{
void CheckGLError(const char *file, int line);
}

#ifndef TONIC_CONFIG_RELEASE
#define TONIC_CHECK_GL_ERROR() ::tonic::graphics::CheckGLError(__FILE__, __LINE__)
#else
#define TONIC_CHECK_GL_ERROR (void *)0
#endif