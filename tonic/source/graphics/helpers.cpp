#include "tonic/graphics/helpers.h"
#include "tonic/log.h"
#include <string>
#include <GL/gl3w.h>

namespace tonic::graphics
{
void CheckGLError(const char *file, int line)
{
    bool hasError = false;
    GLenum error = glGetError();
    while (error != GL_NO_ERROR)
    {
        std::string errorstr;
        switch (error)
        {
        case GL_INVALID_OPERATION:				errorstr = "INVALID_OPERATION";		break;
        case GL_INVALID_ENUM:					errorstr = "GL_INVALID_ENUM";		break;
        case GL_INVALID_VALUE:					errorstr = "GL_INVALID_VALUE";		break;
        case GL_OUT_OF_MEMORY:					errorstr = "GL_OUT_OF_MEMORY";		break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:	errorstr = "GL_INVALID_FRAMEBUFFER_OPERATION";		break;
        default:								errorstr = std::to_string(error);	break;
        }

        TONIC_ERROR("OpenGL Error: %s\nFile: %s:%i", errorstr.c_str(), file, line);
        error = glGetError();
        hasError = true;
    }

    if (hasError) TONIC_BREAK();
}
}