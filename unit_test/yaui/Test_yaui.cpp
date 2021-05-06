#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch2/catch.hpp>
#include <SDL2/SDL.h>
#include "component/Component.h"
#include "gles2/Buffer.h"
#include "Director.h"
#include "gles2/Shader.h"
#include "gles2/Texture.h"
#include "Utility.h"
#include "Scene.h"

TEST_CASE("Draw rectangle", "[yaui]") {
    auto pScene = std::make_shared<yaui::Scene>("Rect");
    auto pDirector = yaui::Director::getInstance();
    pDirector->pushScene(pScene);
    const auto &renderer = pScene->getRenderer();
    auto mvp = renderer.getMVP_Matrix();
    const auto [winWidth, winHeight] = renderer.getWindow()->getSize();

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

    yaui::gles2::BufferLayout layout {
        {"colour", 1, 4, GL_FLOAT, GL_FALSE, offsetof(Pixel, colour)},
        {"position", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
    };

    // Create a Vertex Buffer Object and copy the vertex data to it
    yaui::gles2::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);
    vb.bind();

    // Create a Vertex Array Buffer Object and copy the indices to it
    yaui::gles2::VertexArrayBuffer va({0, 1, 2, 0, 3, 2,});
    va.bind();

    yaui::gles2::Shader shader(
        "HelloWorld",
        yaui::readFile("shaders/vertex.glsl").c_str(),
        yaui::readFile("shaders/fragment.glsl").c_str(),
        layout
    );
    shader.bind();
    shader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());

    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        renderer.clearScreen(0.f, 0.f, 0.f, 0.f);

        // Draw call
        renderer.drawElements(va);

        // Present the result to the screen
        renderer.render();
    }

    pDirector->popScene();
    pDirector->quit();
}

TEST_CASE("Draw lenna using texture", "[yaui]") {
    auto pScene = std::make_shared<yaui::Scene>("Lenna");
    auto pDirector = yaui::Director::getInstance();
    pDirector->pushScene(pScene);
    const auto &renderer = pScene->getRenderer();
    const auto [winWidth, winHeight] = pScene->getRenderer().getWindow()->getSize();

    int32_t width = 0, height = 0, channels = 0;
    std::vector<uint8_t> imagePixelData;
    yaui::loadImage("Lenna.png", imagePixelData, width, height, channels);

    yaui::gles2::Texture texture(imagePixelData.data(), width, height, channels, GL_RGBA);
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
    yaui::gles2::BufferLayout layout {
        {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
        {"aTextureCoordinate", 1, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, textureCoordinate)},
    };
    yaui::gles2::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);
    vb.bind();

    yaui::gles2::VertexArrayBuffer va({0, 1, 2, 0, 3, 2});
    va.bind();

    yaui::gles2::Shader shader(
        "HelloTexture",
        yaui::readFile("shaders/texture.vert.glsl").c_str(),
        yaui::readFile("shaders/texture.frag.glsl").c_str(),
        layout
    );
    shader.bind();
    shader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());

    for(bool loop = true; loop;) {
        for(SDL_Event e; SDL_PollEvent(&e);) {
            if(e.type == SDL_QUIT) loop = false;
        }

        // Clear the screen to black
        renderer.clearScreen(0.f, 0.f, 0.f, 0.f);

        // Draw call
        renderer.drawElements(va);

        // Present the result to the screen
        renderer.render();
    }

    pDirector->popScene();
    pDirector->quit();
}

TEST_CASE("Draw text", "[yaui]") {
    auto pScene = std::make_shared<yaui::Scene>("Text");
    auto pDirector = yaui::Director::getInstance();
    pDirector->pushScene(pScene);
    const auto &renderer = pScene->getRenderer();
    const auto [winWidth, winHeight] = pScene->getRenderer().getWindow()->getSize();

    int32_t width, height, fontSize = 64;
    std::vector<uint8_t> charPixelData;
    std::vector<stbtt_bakedchar> bakedChars;
    yaui::loadBasicAsciiFont("open-sans/OpenSans-Regular.ttf", fontSize, charPixelData, width, height, bakedChars);
    yaui::gles2::Texture texture(charPixelData.data(), width, height, 1, GL_ALPHA);
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

    yaui::gles2::BufferLayout layout {
        {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, position)},
        {"aTextureCoordinate", 1, 2, GL_FLOAT, GL_FALSE, offsetof(Pixel, textureCoordinate)},
    };
    yaui::gles2::VertexBuffer vb(pixelData.data(), sizeof(decltype(pixelData)::value_type), pixelData.size(), layout);
    vb.bind();

    yaui::gles2::VertexArrayBuffer va;
    auto &indices = va.getVertexArray();
    for(uint32_t i = 0; i < pixelData.size(); i+=4) {
        indices.insert(indices.end(), {i+0, i+1, i+2});
        indices.insert(indices.end(), {i+0, i+3, i+2});
    }
    va.bind();

    yaui::gles2::Shader shader(
        "HelloTexture",
        yaui::readFile("shaders/text.vert.glsl").c_str(),
        yaui::readFile("shaders/text.frag.glsl").c_str(),
        layout
    );
    shader.bind();
    shader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());

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
        renderer.render();
    }

    pDirector->popScene();
    pDirector->quit();
}

TEST_CASE("Draw rectangle using yaui", "[yaui]") {
    auto pDirector = yaui::Director::getInstance();
    CHECK(pDirector != nullptr);

    auto pScene = std::make_shared<yaui::Scene>("2 Triangles");
    auto &registry = pScene->getRegistry();

    auto entity = registry.create();
    registry.emplace<yaui::component::Transform>(entity, yaui::component::Transform{
        glm::vec4 {100.f, 100.f, 200.f, 200.f},
        glm::vec2 {1.f, 1.f},
        glm::quat {},
        glm::vec4 {1.0f, 0.0f, 0.0f, 1.0f}
    });

    entity = registry.create();
    registry.emplace<yaui::component::Transform>(entity, yaui::component::Transform{
        glm::vec4 {300.f, 300.f, 100.f, 100.f},
        glm::vec2 {1.f, 1.f},
        glm::quat {},
        glm::vec4 {0.0f, 1.0f, 0.0f, 1.0f}
    });

    pDirector->pushScene(pScene);
    // blocking
    pDirector->run();
    // cleanup
    pDirector->popScene();
}
