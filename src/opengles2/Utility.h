#ifndef YAUI_UTILITY_H
#define YAUI_UTILITY_H


#include <GLES2/gl2.h>

#if NDEBUG
#define debugGlCall(x) x
#else
#define debugGlCall(x)                  \
yaui::glFlushErrors();                  \
x;                                      \
yaui::glLogError(__FILE__, __LINE__)
#endif

namespace yaui {
    void glFlushErrors();
    void glLogError(const char *file, int line);
    GLuint loadShader(GLenum type, const char *shaderSource);
}

#endif //YAUI_UTILITY_H
