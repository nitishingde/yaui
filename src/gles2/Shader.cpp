#include <vector>
#include "Shader.h"

GLuint yaui::gles2::Shader::compileShader(GLenum type, const char *shaderSource) {
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
            YAUI_LOG_ERROR("[OpenGL Shader]:\n{}\n", infoLog.data());
        }

        debugGlCall(glDeleteShader(shader));
        return 0;
    }

    return shader;
}

yaui::gles2::Shader::Shader(const char *pName)
    : mName(pName)
    , mProgramId(glCreateProgram()) {
}

yaui::gles2::Shader::Shader(const char *pName, const char *vertexShaderSource, const char *fragmentShaderSource, const VertexBufferLayout &vertexBufferLayout)
    : mName(pName)
    , mProgramId(glCreateProgram())
    , mVertexShaderId(compileShader(GL_VERTEX_SHADER, vertexShaderSource))
    , mFragmentShaderId(compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource))
    , mVertexBufferLayout(vertexBufferLayout) {
}

yaui::gles2::Shader::~Shader() {
    debugGlCall(glDeleteProgram(mProgramId));
    if(glIsShader(mVertexShaderId)) {
        debugGlCall(glDeleteShader(mVertexShaderId));
    }
    if(glIsShader(mFragmentShaderId)) {
        debugGlCall(glDeleteShader(mFragmentShaderId));
    }
}

void yaui::gles2::Shader::compile(const char *vertexShaderSource, const char *fragmentShaderSource) {
    mVertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    mFragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
}

void yaui::gles2::Shader::bind() const {
    // set attribute locations
    for(const auto &layout: mVertexBufferLayout) {
        debugGlCall(glEnableVertexAttribArray(layout.location));
        debugGlCall(glVertexAttribPointer(layout.location, layout.size, layout.type, layout.isNormalised, layout.stride, (void*)layout.offset));
    }

    // check if program is already linked
    GLint isLinked = 0;
    debugGlCall(glGetProgramiv(mProgramId, GL_LINK_STATUS, &isLinked));
    if(isLinked == GL_FALSE) {
        // Set attribute locations
        for(const auto &layout: mVertexBufferLayout) {
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
            YAUI_LOG_ERROR("[OpenGL Shader]:\n{}\n", infoLog.data());

            debugGlCall(glDeleteShader(mVertexShaderId));
            debugGlCall(glDeleteShader(mFragmentShaderId));
            debugGlCall(glDeleteProgram(mProgramId));
        }
    }

    debugGlCall(glUseProgram(mProgramId));
}

void yaui::gles2::Shader::unbind() const {
    debugGlCall(glUseProgram(0));
}

void yaui::gles2::Shader::setVertexBufferLayout(const yaui::gles2::VertexBufferLayout &vertexBufferLayout) {
    mVertexBufferLayout = vertexBufferLayout;
}

void yaui::gles2::Shader::setUniformMatrix4f(const char *uniformName, const glm::mat4 &projectionMatrix) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, uniformName));
    debugGlCall(glUniformMatrix4fv(location, 1, GL_FALSE, &projectionMatrix[0][0]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::i32vec1 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1i(location, vector[0]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::i32vec2 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform2i(location, vector[0], vector[1]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::i32vec3 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform3i(location, vector[0], vector[1], vector[2]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::i32vec4 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform4i(location, vector[0], vector[1], vector[2], vector[3]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::i32vec1 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1iv(location, 1, &vector[0]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::i32vec2 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1iv(location, 2, &vector[0]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::i32vec3 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1iv(location, 3, &vector[0]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::i32vec4 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1iv(location, 4, &vector[0]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::vec1 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1f(location, vector[0]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::vec2 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform2f(location, vector[0], vector[1]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::vec3 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform3f(location, vector[0], vector[1], vector[2]));
}

void yaui::gles2::Shader::setUniformVector(const char *pUniformName, const glm::vec4 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform4f(location, vector[0], vector[1], vector[2], vector[3]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::vec1 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1fv(location, 1, &vector[0]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::vec2 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1fv(location, 2, &vector[0]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::vec3 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1fv(location, 3, &vector[0]));
}

void yaui::gles2::Shader::setUniformVectorValues(const char *pUniformName, const glm::vec4 &vector) const {
    debugGlCall(auto location = glGetUniformLocation(mProgramId, pUniformName));
    debugGlCall(glUniform1fv(location, 4, &vector[0]));
}
