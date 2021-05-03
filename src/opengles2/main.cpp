#include <SDL2/SDL.h>
#include "Buffer.h"
#include "Director.h"
#include "Shader.h"
#include "stb_image.h"
#include "Texture.h"
#include "Utility.h"

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

    int32_t width = 0, height = 0, channels = 0;
    std::vector<uint8_t> imagePixelData;
    yaui::loadImage("Lenna.png", imagePixelData, width, height, channels);

    yaui::Texture texture(imagePixelData.data(), width, height, channels, GL_RGBA);
    texture.bind();
    imagePixelData.clear();

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

    int32_t width, height, fontSize = 64;
    std::vector<uint8_t> charPixelData;
    std::vector<stbtt_bakedchar> bakedChars;
    yaui::loadBasicAsciiFont("open-sans/OpenSans-Regular.ttf", fontSize, charPixelData, width, height, bakedChars);
    yaui::Texture texture(charPixelData.data(), width, height, 1, GL_ALPHA);
    charPixelData.clear();
    texture.bind();

    struct Pixel {
        glm::vec2 position;
        glm::vec2 textureCoordinate;
    };

    std::vector<Pixel> pixelData;
    float x = winWidth*0.1f, y = winHeight*0.5f;
    for(auto ch: "the quick brown fox jumps over a lazy dog. THE QUICK BROWN FOX JUMPS OVER A LAZY DOG. ~!@#$%^&*()_+{}|:\"<>? `1234567890-=[]\\;',./") {
        stbtt_aligned_quad quad;
        if(0.9*winWidth < x) {
            x = winWidth*0.1f;
            y -= fontSize;
        }
        stbtt_yaui_GetBakedQuadInverted(bakedChars.data(), width, height, ch, &x, &y, &quad, 1);
        pixelData.emplace_back(Pixel {{quad.x0, quad.y0}, {quad.s0, quad.t0}});
        pixelData.emplace_back(Pixel {{quad.x1, quad.y0}, {quad.s1, quad.t0}});
        pixelData.emplace_back(Pixel {{quad.x1, quad.y1}, {quad.s1, quad.t1}});
        pixelData.emplace_back(Pixel {{quad.x0, quad.y1}, {quad.s0, quad.t1}});
    }

    yaui::BufferLayout layout {
        {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
        {"aTextureCoordinate", 1, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, textureCoordinate)},
    };
    yaui::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);
    vb.bind();

    std::vector<uint32_t> indices;
    for(uint32_t i = 0; i < pixelData.size(); i+=4) {
        indices.insert(indices.end(), {i+0, i+1, i+2});
        indices.insert(indices.end(), {i+0, i+3, i+2});
    }
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

    return 0;
}
