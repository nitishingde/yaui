#ifndef YAUI_SHADER_H
#define YAUI_SHADER_H


#include "Types.h"

namespace yaui {
    class Shader {
    private:
        String mName;
        GLuint mProgramId;
        GLuint mVertexShaderId;
        GLuint mFragmentShaderId;
        BufferLayout mBufferLayout;
    private:
        GLuint compileShader(GLenum type, const char *shaderSource);

    public:
        explicit Shader(yaui::String name, const char *vertexShaderSource, const char *fragmentShaderSource, const BufferLayout &bufferLayout);
        ~Shader();
        void bind() const;
        void unbind() const;
    };
}


#endif //YAUI_SHADER_H
