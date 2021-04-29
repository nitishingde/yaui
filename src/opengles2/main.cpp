#include <SDL2/SDL.h>
#include "Buffer.h"
#include "Director.h"
#include "Shader.h"
#include "stb_image.h"
#include "Utility.h"

void helloRect() {
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
    vb.bind();

    std::vector<uint32_t> indices {
        0, 1, 2,
        1, 3, 2,
    };

    // Create a Vertex Array Buffer Object and copy the indices to it
    yaui::VertexArrayBuffer va(indices.data(), indices.size());
    va.bind();

    yaui::Shader shader(
        "HelloWorld",
        yaui::readFile("vertex.glsl").c_str(),
        yaui::readFile("fragment.glsl").c_str(),
        layout
    );
    shader.bind();

    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        debugGlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        debugGlCall(glClear(GL_COLOR_BUFFER_BIT));

        // Draw call
        debugGlCall(glDrawElements(GL_TRIANGLES, va.getSize(), va.getType(), nullptr));
        SDL_GL_SwapWindow(pWindow);
    }

    yaui::Director::getInstance()->quit();
}

void helloTexture() {
    auto pWindow = yaui::Director::getInstance()->getWindow();

    struct Pixel {
        yaui::Vec2 position;
        yaui::Vec2 textureCoordinate;
    };

    std::vector<Pixel> pixelData {
        {{-0.5f, -0.5f}, {0.f, 0.f}},// bottom left
        {{-0.5f, 0.5f}, {0.f, 1.f}},// top left
        {{0.5f, 0.5f}, {1.f, 1.f}},// top right
        {{0.5f, -0.5f}, {1.f, 0.f}},// bottom right
    };
    yaui::BufferLayout layout {
        {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
        {"aTextureCoordinate", 1, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, textureCoordinate)},
    };
    yaui::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);
    vb.bind();

    std::vector<uint32_t> indices {
        0, 1, 2,
        2, 3, 0,
    };
    yaui::VertexArrayBuffer va(indices.data(), indices.size());
    va.bind();

    yaui::Shader shader(
        "HelloTexture",
        yaui::readFile("texture.vert.glsl").c_str(),
        yaui::readFile("texture.frag.glsl").c_str(),
        layout
    );
    shader.bind();

    srand(time(nullptr));
    stbi_set_flip_vertically_on_load(1);
    int32_t width, height, channels;
    auto image = stbi_load(rand()%2 ? "2048x1024.png": "Lenna.png", &width, &height, &channels, STBI_rgb_alpha);

    GLuint texture;
    debugGlCall(glGenTextures(1, &texture));
    debugGlCall(glBindTexture(GL_TEXTURE_2D, texture));
    // set the texture wrapping/filtering options (on the currently bound texture object)
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    debugGlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
    debugGlCall(glBindTexture(GL_TEXTURE_2D, texture));
    stbi_image_free(image);

    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        debugGlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        debugGlCall(glClear(GL_COLOR_BUFFER_BIT));

        // Draw the texture
        debugGlCall(glDrawElements(GL_TRIANGLES, va.getSize(), va.getType(), nullptr));

        // Draw call
        SDL_GL_SwapWindow(pWindow);
    }

    yaui::Director::getInstance()->quit();
}

int main(int argc, char** argv) {
    helloRect();
    helloTexture();
}
