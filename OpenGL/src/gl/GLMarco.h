#pragma once
#ifndef GLMACRO
#define GLMACRO

#include <GL/glew.h>
#include <iostream>

class GLMacro
{
public:
    static void GLClearError();
    static bool GLLogCall(const char* function, const char* file, int line);
};


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLMacro::GLClearError();\
    x;\
    ASSERT(GLMacro::GLLogCall(#x, __FILE__, __LINE__));

#endif