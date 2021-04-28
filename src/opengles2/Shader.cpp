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

yaui::Shader::Shader(yaui::String name)
    : mName(std::move(name))
    , mId(0) {
}

yaui::Shader::~Shader() {
    debugGlCall(glDeleteProgram(mId));
}

void yaui::Shader::loadShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
    mId = glCreateProgram();

    auto vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    debugGlCall(glAttachShader(mId, vertexShader));

    auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    debugGlCall(glAttachShader(mId, fragmentShader));

    debugGlCall(glLinkProgram(mId));

    GLint isLinked = 0;
    debugGlCall(glGetProgramiv(mId, GL_LINK_STATUS, &isLinked));
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        debugGlCall(glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &maxLength));

        std::vector<GLchar> infoLog(maxLength);
        debugGlCall(glGetProgramInfoLog(mId, maxLength, &maxLength, infoLog.data()));
        debugGlCall(glDeleteProgram(mId));
        debugGlCall(glDeleteShader(vertexShader));
        debugGlCall(glDeleteShader(fragmentShader));
        spdlog::error("[OpenGL Shader]:\n{}\n", infoLog.data());
    }

    debugGlCall(glDetachShader(mId, vertexShader));
    debugGlCall(glDeleteShader(vertexShader));

    debugGlCall(glDetachShader(mId, fragmentShader));
    debugGlCall(glDeleteShader(fragmentShader));
}

void yaui::Shader::bind() const {
    debugGlCall(glUseProgram(mId));
}

void yaui::Shader::unbind() const {
    debugGlCall(glUseProgram(0));
}

GLuint yaui::Shader::getProgramId() const {
    return mId;
}
