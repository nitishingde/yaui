#include <numeric>
#include "System.h"
#include "component/Component.h"
#include "gles2/Texture.h"

bool yaui::system::ISystem::operator<(const ISystem &other) const {
    return this->priorityRank < other.priorityRank;
}

yaui::system::RenderingBackgroundSystem::RenderingBackgroundSystem(uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    mBackgroundShader.compile(
        yaui::readFile("shaders/yaui/background.vert.glsl").c_str(),
        yaui::readFile("shaders/yaui/background.frag.glsl").c_str()
    );
}

void yaui::system::RenderingBackgroundSystem::executeJob(entt::registry &registry, gles2::Renderer &renderer) {
    auto &quadVertexInfo = registry.ctx<gles2::QuadVertexInfo>();
    auto &quadVertices = quadVertexInfo.quadVertices;
    std::vector<uint32> vertexArray;

    auto view = registry.view<component::Transform>();
    for(auto entity: view) {
        auto entityIdx = static_cast<uint32>(entity)<<2;
        auto &viewPort = view.get(entity).viewPort;
        auto &colour = view.get(entity).colour;
        quadVertices[entityIdx+0].colour = colour;
        quadVertices[entityIdx+0].position = {viewPort.x, viewPort.y};
        quadVertices[entityIdx+1].colour = colour;
        quadVertices[entityIdx+1].position = {viewPort.x, viewPort.y + viewPort.w};
        quadVertices[entityIdx+2].colour = colour;
        quadVertices[entityIdx+2].position = {viewPort.x + viewPort.z, viewPort.y + viewPort.w};
        quadVertices[entityIdx+3].colour = colour;
        quadVertices[entityIdx+3].position = {viewPort.x + viewPort.z, viewPort.y};
        vertexArray.insert(vertexArray.end(), {entityIdx+0, entityIdx+1, entityIdx+2, entityIdx+0, entityIdx+2, entityIdx+3});
    }

    auto &vertexBuffer = quadVertexInfo.vertexBuffer;
    vertexBuffer.setBufferData(quadVertices.data(), quadVertices.size() * sizeof(std::remove_reference<decltype(quadVertices)>::type::value_type));
    vertexBuffer.bind();

    gles2::VertexArrayBuffer vertexArrayBuffer(vertexArray);
    vertexArrayBuffer.bind();

    mBackgroundShader.setVertexBufferLayout(quadVertexInfo.vertexBufferLayout);
    mBackgroundShader.bind();
    mBackgroundShader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());

    renderer.drawElements(vertexArrayBuffer);
}

yaui::system::RenderingTextureSystem::RenderingTextureSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    mTextureShader.compile(
        yaui::readFile("shaders/yaui/texture.vert.glsl").c_str(),
        yaui::readFile("shaders/yaui/texture.frag.glsl").c_str()
    );
}

void yaui::system::RenderingTextureSystem::initialiseForRendering(entt::registry &registry, yaui::gles2::Renderer &renderer) {
    auto &quadVertexInfo = registry.ctx<gles2::QuadVertexInfo>();
    auto &quadVertices = quadVertexInfo.quadVertices;

    auto view = registry.view<component::Texture>();
    uint8 textureSlot = 0;
    for(auto entity: view) {
        auto entityIdx = static_cast<uint32>(entity)<<2;
        quadVertices[entityIdx+0].textureCoordinate = {0.f, 0.f};
        quadVertices[entityIdx+0].textureIndex = float(textureSlot);
        quadVertices[entityIdx+1].textureCoordinate = {0.f, 1.f};
        quadVertices[entityIdx+1].textureIndex = float(textureSlot);
        quadVertices[entityIdx+2].textureCoordinate = {1.f, 1.f};
        quadVertices[entityIdx+2].textureIndex = float(textureSlot);
        quadVertices[entityIdx+3].textureCoordinate = {1.f, 0.f};
        quadVertices[entityIdx+3].textureIndex = float(textureSlot);
        textureSlot++;
        if(textureSlot == TEXTURE_SLOTS_MAX_LIMIT) textureSlot = 0;
    }

    auto &vertexBuffer = quadVertexInfo.vertexBuffer;
    vertexBuffer.setBufferData(quadVertices.data(), quadVertices.size() * sizeof(std::remove_reference<decltype(quadVertices)>::type::value_type));
    vertexBuffer.bind();

    mTextureShader.setVertexBufferLayout(quadVertexInfo.vertexBufferLayout);
    mTextureShader.bind();
    mTextureShader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());
    std::vector<int32> samplers(TEXTURE_SLOTS_MAX_LIMIT);
    std::iota(samplers.begin(), samplers.end(), 0);
    mTextureShader.setUniformVectorValues("uSampler[0]", samplers);
}

void yaui::system::RenderingTextureSystem::executeJob(entt::registry &registry, yaui::gles2::Renderer &renderer) {
    initialiseForRendering(registry, renderer);

    // batch rendering
    auto view = registry.view<component::Texture>();
    for(auto it = view.begin(), end = view.end(); it != end;) {
        std::vector<gles2::Texture> textures(TEXTURE_SLOTS_MAX_LIMIT);
        std::vector<uint32> vertexArray;
        for(uint8 textureSlot = 0; textureSlot < TEXTURE_SLOTS_MAX_LIMIT and it != end; ++textureSlot, ++it) {
            auto entityIdx = static_cast<uint32>(*it)<<2;
            auto &textureComp = view.get(*it);
            textures[textureSlot].bind(textureSlot);
            textures[textureSlot].setTextureData(textureComp.pixelData.data(), textureComp.width, textureComp.height, textureComp.channelFormat);
            vertexArray.insert(vertexArray.end(), {entityIdx+0, entityIdx+1, entityIdx+2, entityIdx+0, entityIdx+2, entityIdx+3});
        }
        gles2::VertexArrayBuffer vertexArrayBuffer(vertexArray);
        vertexArrayBuffer.bind();
        renderer.drawElements(vertexArrayBuffer);
    }
}
