#include "tonic/graphics/helpers.h"
#include "tonic/log.h"
#include <string>
#include <GL/gl3w.h>

namespace tonic::graphics
{
static const char *const sOpenGLErrors[] = 
{
    "INVALID_ENUM",
    "INVALID_VALUE",
    "INVALID_OPERATION",
    "STACK_OVERFLOW",
    "STACK_UNDERFLOW",
    "OUT_OF_MEMORY",
    "INVALID_FRAMEBUFFER_OPERATION",
    "CONTEXT_LOST"
};

void CheckGLError(const char *file, int line)
{
    bool hasError = false;
    GLenum error = glGetError();

    while (error != GL_NO_ERROR)
    {
        std::string errorstr;

        switch (error)
        {
        case GL_INVALID_ENUM:
        case GL_INVALID_VALUE:
        case GL_INVALID_OPERATION:
        case GL_STACK_OVERFLOW:
        case GL_STACK_UNDERFLOW:
        case GL_OUT_OF_MEMORY:
        case GL_INVALID_FRAMEBUFFER_OPERATION:
        case GL_CONTEXT_LOST:
            errorstr = sOpenGLErrors[error - GL_INVALID_ENUM];
            break;
        [[unlikely]] default:					
            errorstr = std::to_string(error);	
            break;
        }

        TONIC_ERROR("OpenGL Error: %s\nFile: %s:%i", errorstr.c_str(), file, line);
        error = glGetError();
        hasError = true;
    }

    if (hasError) TONIC_BREAK();
}
}