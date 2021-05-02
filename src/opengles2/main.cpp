#include <SDL2/SDL.h>
#include "Buffer.h"
#include "Director.h"
#include "Shader.h"
#include "stb_image.h"
#include "Texture.h"
#include "Utility.h"
#include "stb_truetype.h"

void helloRect() {
    auto pDirector = yaui::Director::getInstance();
    auto pWindow = pDirector->getWindow();
    const auto [winWidth, winHeight] = pDirector->getWindowSize();

    struct Pixel {
        glm::vec2 position;
        glm::vec4 colour;
    };

    std::vector<Pixel> pixelData {
        {{winWidth/2.f - 100.f, winHeight/2.f - 100.f}, {1.f, 0.f, 0.f, 1.f}},  // bottom left
        {{winWidth/2.f + 100.f, winHeight/2.f - 100.f}, {0.f, 1.f, 0.f, 1.f}},  // bottom right
        {{winWidth/2.f + 100.f, winHeight/2.f + 100.f}, {0.f, 0.f, 1.f, 1.f}},  // top right
        {{winWidth/2.f - 100.f, winHeight/2.f + 100.f}, {1.f, 1.f, 1.f, 1.f}},  // top left
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
        0, 3, 2,
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
    shader.setUniformMatrix4f("uMVP", pDirector->getMVP_Matrix());

    const auto &renderer = pDirector->getRenderer();
    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        renderer.clearScreen(0.f, 0.f, 0.f, 0.f);

        // Draw call
        renderer.drawElements(va);

        // Present the result to the screen
        renderer.present(pWindow);
    }

    pDirector->quit();
}

void helloTexture() {
    auto pDirector = yaui::Director::getInstance();
    auto pWindow = pDirector->getWindow();
    const auto [winWidth, winHeight] = pDirector->getWindowSize();

    yaui::Texture texture;
    texture.loadImage("Lenna.png");
    const auto [width, height] = texture.getDimension();
    texture.bind();

    struct Pixel {
        glm::vec2 position;
        glm::vec2 textureCoordinate;
    };

    std::vector<Pixel> pixelData {
        {{winWidth/2.f - width/2.f, winHeight/2.f - height/2.f}, {0.f, 0.f}},// bottom left
        {{winWidth/2.f + width/2.f, winHeight/2.f - height/2.f}, {1.f, 0.f}},// bottom right
        {{winWidth/2.f + width/2.f, winHeight/2.f + height/2.f}, {1.f, 1.f}},// top right
        {{winWidth/2.f - width/2.f, winHeight/2.f + height/2.f}, {0.f, 1.f}},// top left
    };
    yaui::BufferLayout layout {
        {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
        {"aTextureCoordinate", 1, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, textureCoordinate)},
    };
    yaui::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);
    vb.bind();

    std::vector<uint32_t> indices {
        0, 1, 2,
        0, 3, 2,
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
    shader.setUniformMatrix4f("uMVP", pDirector->getMVP_Matrix());

    const auto &renderer = pDirector->getRenderer();
    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        renderer.clearScreen(0.f, 0.f, 0.f, 0.f);

        // Draw call
        renderer.drawElements(va);

        // Present the result to the screen
        renderer.present(pWindow);
    }

    pDirector->quit();
}

void helloText() {
    auto pDirector = yaui::Director::getInstance();
    auto pWindow = pDirector->getWindow();
    const auto [winWidth, winHeight] = pDirector->getWindowSize();

    auto fontFile = yaui::readFile("open-sans/OpenSans-Regular.ttf");
    int width = 512, height = 512;
    std::vector<uint8_t> charPixelData(width*height);
    std::vector<stbtt_bakedchar> bakedChars(95);
    if(stbtt_BakeFontBitmap((unsigned char *)fontFile.data(), 0, 64, charPixelData.data(), width, height, 32, 95, bakedChars.data()) == 0) {
        return;
    }
    yaui::Texture texture(charPixelData.data(), width, height, 1, GL_ALPHA);
    texture.bind();

    struct Pixel {
        glm::vec2 position;
        glm::vec2 textureCoordinate;
    };

    std::vector<Pixel> pixelData {
        {{winWidth/2.f - width/2.f, winHeight/2.f - height/2.f}, {0.f, 1.f}},// bottom left
        {{winWidth/2.f + width/2.f, winHeight/2.f - height/2.f}, {1.f, 1.f}},// bottom right
        {{winWidth/2.f + width/2.f, winHeight/2.f + height/2.f}, {1.f, 0.f}},// top right
        {{winWidth/2.f - width/2.f, winHeight/2.f + height/2.f}, {0.f, 0.f}},// top left
    };
    yaui::BufferLayout layout {
        {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
        {"aTextureCoordinate", 1, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, textureCoordinate)},
    };
    yaui::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);
    vb.bind();

    std::vector<uint32_t> indices {
        0, 1, 2,
        0, 3, 2,
    };
    yaui::VertexArrayBuffer va(indices.data(), indices.size());
    va.bind();

    yaui::Shader shader(
        "HelloTexture",
        yaui::readFile("text.vert.glsl").c_str(),
        yaui::readFile("text.frag.glsl").c_str(),
        layout
    );
    shader.bind();
    shader.setUniformMatrix4f("uMVP", pDirector->getMVP_Matrix());

    const auto &renderer = pDirector->getRenderer();
    renderer.enableBlend();
    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        renderer.clearScreen(0.5f, 0.5f, 0.5f, 1.f);

        // Draw call
        renderer.drawElements(va);

        // Present the result to the screen
        renderer.present(pWindow);
    }

    pDirector->quit();
}

int main(int argc, char** argv) {
    helloRect();
    helloTexture();
    helloText();
}
