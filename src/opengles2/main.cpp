#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>
#include "Director.h"
#include "Utility.h"
#include "Buffer.h"
#include "Shader.h"
#include "Types.h"

int main(int argc, char** argv) {
    auto pWindow = yaui::Director::getInstance()->getWindow();

    struct Pixel {
        yaui::Vec2 position;
        yaui::Colour colour;
    };

    std::vector<Pixel> pixelData {
        {{-0.5f,-0.5f}, {1.f, 0.f, 0.f, 1.f}},
        {{-0.5f,0.5f},  {0.f, 1.f, 0.f, 1.f}},
        {{ 0.5f,-0.5f}, {0.f, 0.f, 1.f, 1.f}},
        {{0.5f, 0.5f},  {1.f, 1.f, 1.f, 1.f}},
    };

    yaui::BufferLayout layout {
        {"colour", 1, 4, GL_FLOAT, GL_FALSE, offsetof(Pixel, colour)},
        {"position", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
    };

    // Create a Vertex Buffer Object and copy the vertex data to it
    yaui::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);

    std::vector<uint32_t> indices {
        0, 1, 2,
        1, 3, 2,
    };

    // Create a Vertex Array Buffer Object and copy the indices to it
    yaui::VertexArrayBuffer va(indices.data(), indices.size());

    yaui::Shader shader(
        "HelloWorld",
        yaui::readFile("vertex.glsl").c_str(),
        yaui::readFile("fragment.glsl").c_str(),
        layout
    );

    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        debugGlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        debugGlCall(glClear(GL_COLOR_BUFFER_BIT));

        // Draw call
        vb.bind();
        va.bind();
        shader.bind();
        debugGlCall(glDrawElements(GL_TRIANGLES, va.getSize(), va.getType(), nullptr));
        vb.bind();
        va.unbind();
        shader.unbind();
        SDL_GL_SwapWindow(pWindow);
    }

    yaui::Director::getInstance()->quit();
}
