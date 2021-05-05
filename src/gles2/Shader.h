#ifndef YAUI_SHADER_H
#define YAUI_SHADER_H


#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include "Buffer.h"
#include "Types.h"
#include "Utility.h"

namespace yaui::gles2 {
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
        explicit Shader(yaui::String name, const char *vertexShaderSource, const char *fragmentShaderSource, BufferLayout bufferLayout);
        ~Shader();
        Shader(const Shader &other) = delete;
        Shader& operator=(const Shader &other) = delete;
        Shader(Shader &&other) = delete;
        Shader& operator=(Shader &&other) = delete;
        void bind() const;
        void unbind() const;
        void setUniformMatrix4f(const char *uniformName, const glm::mat4 &projectionMatrix) const;//FIXME: make it generic
    };
}


#endif //YAUI_SHADER_H
