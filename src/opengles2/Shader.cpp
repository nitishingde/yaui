#include "Shader.h"
#include <utility>
#include <vector>
#include <spdlog/spdlog.h>
#include "Utility.h"

GLuint yaui::Shader::compileShader(GLenum type, const char *shaderSource) {
    GLuint shader;
    GLint compiled;

    // Create the shader object
    debugGlCall(shader = glCreateShader(type));
    if (shader == 0) {
        return 0;
    }

    // Load the shader source
    debugGlCall(glShaderSource(shader, 1, &shaderSource, nullptr));

    // Compile the shader
    debugGlCall(glCompileShader(shader));

    // Check the compile status
    debugGlCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));

    if(!compiled) {
        GLint infoLen = 0;
        debugGlCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen));
        if(infoLen > 1) {
            std::vector<GLchar> infoLog(infoLen);
            debugGlCall(glGetShaderInfoLog(shader, infoLen, nullptr, infoLog.data()));
            spdlog::error("[OpenGL Shader]:\n{}\n", infoLog.data());
        }

        debugGlCall(glDeleteShader(shader));
        return 0;
    }

    return shader;
}

yaui::Shader::Shader(yaui::String name, const char *vertexShaderSource, const char *fragmentShaderSource, const BufferLayout &bufferLayout)
    : mName(std::move(name))
    , mProgramId(glCreateProgram())
    , mVertexShaderId(compileShader(GL_VERTEX_SHADER, vertexShaderSource))
    , mFragmentShaderId(compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource))
    , mBufferLayout(bufferLayout) {
}

yaui::Shader::~Shader() {
    debugGlCall(glDeleteProgram(mProgramId));
    debugGlCall(glDeleteShader(mVertexShaderId));
    debugGlCall(glDeleteShader(mFragmentShaderId));
}

void yaui::Shader::bind() const {
    // check if program is already linked
    GLint isLinked = 0;
    debugGlCall(glGetProgramiv(mProgramId, GL_LINK_STATUS, &isLinked));
    if(isLinked == GL_FALSE) {
        // Set attribute locations
        for(const auto &layout: mBufferLayout) {
            debugGlCall(glBindAttribLocation(mProgramId, layout.location, layout.attribute.c_str()));
        }

        // Link vertex and fragment shaders
        debugGlCall(glAttachShader(mProgramId, mVertexShaderId));
        debugGlCall(glAttachShader(mProgramId, mFragmentShaderId));
        debugGlCall(glLinkProgram(mProgramId));
        // Decrement the reference count for the shaders after linking
        debugGlCall(glDetachShader(mProgramId, mVertexShaderId));
        debugGlCall(glDetachShader(mProgramId, mFragmentShaderId));
        debugGlCall(glGetProgramiv(mProgramId, GL_LINK_STATUS, &isLinked));
        if(isLinked == GL_FALSE) {
            GLint maxLength = 0;
            debugGlCall(glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &maxLength));
            std::vector<GLchar> infoLog(maxLength);
            debugGlCall(glGetProgramInfoLog(mProgramId, maxLength, &maxLength, infoLog.data()));
            spdlog::error("[OpenGL Shader]:\n{}\n", infoLog.data());

            debugGlCall(glDeleteShader(mVertexShaderId));
            debugGlCall(glDeleteShader(mFragmentShaderId));
            debugGlCall(glDeleteProgram(mProgramId));
        }
    }

    debugGlCall(glUseProgram(mProgramId));
}

void yaui::Shader::unbind() const {
    debugGlCall(glUseProgram(0));
}
