#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#include <spdlog/spdlog.h>
#include <fstream>

GLuint LoadShader(GLenum type, const std::string &shaderSource) {
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);
    if (shader == 0) {
        return 0;
    }

    // Load the shader source
    const char *c_str = shaderSource.c_str();
    glShaderSource(shader, 1, &c_str, nullptr);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1) {
            std::vector<char> infoLog(infoLen);
            glGetShaderInfoLog(shader, infoLen, nullptr, infoLog.data());
            spdlog::error("Error compiling shader:\n{}\n", infoLog.data());
        }

        glDeleteShader(shader);
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
    auto glsl_v = glGetString(GL_SHADING_LANGUAGE_VERSION);
    auto gl_v = glGetString(GL_VERSION);
    printf("GL version             : %s\n", gl_v);
    printf("GLSL version supported : %s\n", glsl_v);
    printf("-----------------------------------------------------------------------------\n");

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

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

    Pixel pixelData[] = {
        {{-0.5f, -0.5f}, {1.0f, 0.f, 0.f, 1.f}},
        {{ 0.0f,  0.5f}, {0.0f, 1.f, 0.f, 1.f}},
        {{ 0.5f, -0.5f}, {0.0f, 0.f, 1.f, 1.f}},
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pixelData), pixelData, GL_STATIC_DRAW);

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
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Pixel), (void*)offsetof(Pixel, position));

    posAttrib = glGetAttribLocation(shaderProgram, "colour");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Pixel), (void*)offsetof(Pixel, colour));

    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle from the 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);
    }

    glDeleteBuffers(1, &vbo);

    SDL_GL_DeleteContext(sdlGlCreateContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
