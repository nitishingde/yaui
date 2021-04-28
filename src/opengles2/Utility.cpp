#include "Utility.h"
#include <spdlog/spdlog.h>

void yaui::glFlushErrors() {
    while(glGetError() != GL_NO_ERROR);
}

void yaui::glLogError(const char *file, int line) {
    for(GLenum errorCode = glGetError(); errorCode != GL_NO_ERROR; errorCode = glGetError()) {
        std::string error;
        switch(errorCode) {
            case GL_INVALID_ENUM:                   error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                  error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:              error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                  error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                                error = "UNKNOWN"; break;
        }
        spdlog::error("[OpenGL][file = {}][line = {}]: Error code = {}", file, line, error);
    }
}

GLuint yaui::loadShader(GLenum type, const char *shaderSource)  {
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
            std::vector<char> infoLog(infoLen);
            debugGlCall(glGetShaderInfoLog(shader, infoLen, nullptr, infoLog.data()));
            spdlog::error("[OpenGL Shader]:\n{}\n", infoLog.data());
        }

        debugGlCall(glDeleteShader(shader));
        return 0;
    }

    return shader;
}
