#pragma once

namespace tonic::graphics
{
void CheckGLError();
}

#ifndef TONIC_CONFIG_RELEASE
#define TONIC_CHECK_GL_ERROR() ::tonic::graphics::CheckGLError()
#else
#define TONIC_CHECK_GL_ERROR (void *)0
#endif