#pragma once

#include <glad/glad.h>
#include "../core/Log.h"

namespace Shengine {
    static void GLClearErrors()
    {
        while (glGetError() != GL_NO_ERROR);

    }

    static bool GLLogCall(const char* function, uint32_t line, const char* file)
    {
        while (GLenum error = glGetError())
        {
            CORE_ERROR("[OpenGL Error] ({0}): [{1}] {2} in {3}", error, line, function, file);
            return false;
        }

        return true;
    }
}

#define GLCall(x) Shengine::GLClearErrors();\
    x;\
    CORE_ASSERT(Shengine::GLLogCall(#x, __LINE__, __FILE__), "OpenGL Error")