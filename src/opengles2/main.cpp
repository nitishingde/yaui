#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include "Utility.h"

GLuint LoadShader(GLenum type, const std::string &shaderSource) {
    GLuint shader;
    GLint compiled;

    // Create the shader object
    debugGlCall(shader = glCreateShader(type));
    if (shader == 0) {
        return 0;
    }

    // Load the shader source
    const char *c_str = shaderSource.c_str();
    debugGlCall(glShaderSource(shader, 1, &c_str, nullptr));

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


int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 0;
    }

    auto window = SDL_CreateWindow(
        "test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1080,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_PROFILE_MASK, SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(0);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCELERATED_VISUAL, 1);

    auto sdlGlCreateContext = SDL_GL_CreateContext(window);
    debugGlCall(auto glsl_v = glGetString(GL_SHADING_LANGUAGE_VERSION));
    debugGlCall(auto gl_v = glGetString(GL_VERSION));
    printf("GL version             : %s\n", gl_v);
    printf("GLSL version supported : %s\n", glsl_v);
    printf("-----------------------------------------------------------------------------\n");

    struct vec2 {
        float x;
        float y;
    } __attribute__((aligned(8)));

    struct vec4 {
        float x;
        float y;
        float z;
        float w;
    } __attribute__((aligned(16)));

    struct Pixel {
        vec2 position;
        vec4 colour;
    };

    std::vector<Pixel> pixelData {
        {{-0.5f, -0.5f}, {1.0f, 0.f, 0.f, 1.f}},
        {{ -0.5f,  0.5f}, {0.0f, 1.f, 0.f, 1.f}},
        {{ 0.5f, -0.5f}, {0.0f, 0.f, 1.f, 1.f}},
        {{ 0.5f,  0.5f}, {1.0f, 1.f, 1.f, 1.f}},
    };

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    debugGlCall(glGenBuffers(1, &vbo));
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    debugGlCall(glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(pixelData.size() * sizeof(decltype(pixelData)::value_type)), pixelData.data(), GL_STATIC_DRAW));

    std::vector<uint8_t> indices {
        0, 1, 2,
        1, 3, 2,
    };

    // Create a Vertex Array Buffer Object and copy the indices to it
    GLuint vao;
    debugGlCall(glGenBuffers(1, &vao));
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao));
    debugGlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(indices.size() * sizeof(decltype(indices)::value_type)), indices.data(), GL_STATIC_DRAW));

    // Create and compile the vertex shader
    std::ifstream ifs("vertex.glsl");
    std::string vertexSource((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    printf("%s", vertexSource.c_str());
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexSource);

    // Create and compile the fragment shader
    ifs.close();
    ifs.open("fragment.glsl");
    std::string fragmentSource((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    printf("%s", fragmentSource.c_str());

    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentSource);

    // Link the vertex and fragment shader into a shader program
    debugGlCall(GLuint shaderProgram = glCreateProgram());
    debugGlCall(glAttachShader(shaderProgram, vertexShader));
    debugGlCall(glAttachShader(shaderProgram, fragmentShader));
    debugGlCall(glLinkProgram(shaderProgram));
    debugGlCall(glUseProgram(shaderProgram));

    // Specify the layout of the vertex data
    debugGlCall(GLint posAttrib = glGetAttribLocation(shaderProgram, "position"));
    debugGlCall(glEnableVertexAttribArray(posAttrib));
    debugGlCall(glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Pixel), (void*)offsetof(Pixel, position)));

    debugGlCall(posAttrib = glGetAttribLocation(shaderProgram, "colour"));
    debugGlCall(glEnableVertexAttribArray(posAttrib));
    debugGlCall(glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Pixel), (void*)offsetof(Pixel, colour)));

    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        debugGlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        debugGlCall(glClear(GL_COLOR_BUFFER_BIT));

        // Draw call
        debugGlCall(glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_BYTE, nullptr));
        SDL_GL_SwapWindow(window);
    }

    debugGlCall(glDeleteBuffers(1, &vbo));
    debugGlCall(glDeleteBuffers(1, &vao));

    SDL_GL_DeleteContext(sdlGlCreateContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
