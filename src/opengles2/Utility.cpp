#include "Utility.h"
#include <fstream>
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

yaui::String yaui::readFile(const String &filePath) {
    std::ifstream ifs(filePath);
    return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}
