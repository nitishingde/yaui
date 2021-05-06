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
        GLuint mProgramId = 0;
        GLuint mVertexShaderId = 0;
        GLuint mFragmentShaderId = 0;
        BufferLayout mBufferLayout{};
    private:
        GLuint compileShader(GLenum type, const char *shaderSource);

    public:
        explicit Shader(const char *pName = "");
        explicit Shader(const char *pName, const char *vertexShaderSource, const char *fragmentShaderSource, const BufferLayout &bufferLayout = {});
        ~Shader();
        Shader(const Shader &other) = delete;
        Shader& operator=(const Shader &other) = delete;
        Shader(Shader &&other) = delete;
        Shader& operator=(Shader &&other) = delete;
        void compile(const char *vertexShaderSource, const char *fragmentShaderSource);
        void bind() const;
        void unbind() const;
        void setBufferLayout(const BufferLayout &bufferLayout);
        void setUniformMatrix4f(const char *uniformName, const glm::mat4 &projectionMatrix) const;//FIXME: make it generic
    };
}


#endif //YAUI_SHADER_H
