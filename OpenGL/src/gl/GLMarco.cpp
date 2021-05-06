#include "GLMarco.h"


void GLMacro::GLClearError()
{
#ifdef _DEBUG
    while (glGetError() != GL_NO_ERROR);
#endif
}

bool GLMacro::GLLogCall(const char* function, const char* file, int line)
{
#ifdef _DEBUG
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;

        return false;
    }
#endif
    return true;
}
