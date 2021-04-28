#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>
#include "Director.h"
#include "Utility.h"
#include "VertexBuffer.h"
#include "VertexArrayBuffer.h"
#include "Shader.h"

int main(int argc, char** argv) {
    auto pWindow = yaui::Director::getInstance()->getWindow();

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
    yaui::VertexBuffer vb(pixelData.data(), pixelData.size() * sizeof(decltype(pixelData)::value_type));

    std::vector<uint32_t> indices {
        0, 1, 2,
        1, 3, 2,
    };

    // Create a Vertex Array Buffer Object and copy the indices to it
    yaui::VertexArrayBuffer va(indices.data(), indices.size());

    yaui::Shader shader("HelloWorld");
    shader.loadShader(
        yaui::readFile("vertex.glsl").c_str(),
        yaui::readFile("fragment.glsl").c_str()
    );
    shader.bind();
    auto shaderProgram = shader.getProgramId();

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
        va.bind();
        debugGlCall(glDrawElements(GL_TRIANGLES, va.getSize(), va.getType(), nullptr));
        SDL_GL_SwapWindow(pWindow);
    }

    yaui::Director::getInstance()->quit();
}
