#ifndef YAUI_SHADER_H
#define YAUI_SHADER_H


#include <GLES2/gl2.h>
#include "Types.h"

namespace yaui {
    class Shader {
    private:
        String mName;
        GLuint mId;
        GLuint compileShader(GLenum type, const char *shaderSource);

    public:
        explicit Shader(String name);
        ~Shader();
        void loadShader(const char *vertexShaderSource, const char *fragmentShaderSource);
        void bind() const;
        void unbind() const;
        GLuint getProgramId() const;
    };
}


#endif //YAUI_SHADER_H
