#ifndef YAUI_SHADER_H
#define YAUI_SHADER_H


#include <glm/glm.hpp>
#include "Types.h"
#include "Utility.h"

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
        void setUniformMatrix4f(const char *uniformName, const glm::mat4 &projectionMatrix) const;//FIXME: make it generic
    };
}


#endif //YAUI_SHADER_H
