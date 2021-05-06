#include "System.h"
#include "component/Component.h"

bool yaui::system::ISystem::operator<(const ISystem &other) const {
    return this->priorityRank < other.priorityRank;
}

yaui::system::RenderingBackgroundSystem::RenderingBackgroundSystem(uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    mBackgroundShader.compile(
        yaui::readFile("shaders/background.vert.glsl").c_str(),
        yaui::readFile("shaders/background.frag.glsl").c_str()
    );
}

void yaui::system::RenderingBackgroundSystem::executeJob(entt::registry &registry, gles2::Renderer &renderer) {
    auto &pixelVertexInfo = registry.ctx<gles2::PixelVertexInfo>();
    auto &pixelVertices = pixelVertexInfo.pixelVertices;
    gles2::VertexArrayBuffer vertexArrayBuffer;
    auto &vertexArray = vertexArrayBuffer.getVertexArray();

    auto view = registry.view<component::Transform>();
    uint32 i = 0;
    for(auto entity: view) {
        auto entityIdx = static_cast<uint32>(entity)<<2;
        auto &viewPort = view.get(entity).viewPort;
        auto &colour = view.get(entity).colour;
        pixelVertices[entityIdx+0].colour = colour;
        pixelVertices[entityIdx+0].position = {viewPort.x, viewPort.y};
        pixelVertices[entityIdx+1].colour = colour;
        pixelVertices[entityIdx+1].position = {viewPort.x, viewPort.y + viewPort.w};
        pixelVertices[entityIdx+2].colour = colour;
        pixelVertices[entityIdx+2].position = {viewPort.x + viewPort.z, viewPort.y + viewPort.w};
        pixelVertices[entityIdx+3].colour = colour;
        pixelVertices[entityIdx+3].position = {viewPort.x + viewPort.z, viewPort.y};
        vertexArray.insert(vertexArray.end(), {entityIdx+0, entityIdx+1, entityIdx+2, entityIdx+0, entityIdx+2, entityIdx+3});
    }

    vertexArrayBuffer.bind();

    gles2::VertexBuffer vertexBuffer(pixelVertices.data(), sizeof(gles2::PixelVertex), pixelVertices.size(), pixelVertexInfo.vertexBufferLayout);
    vertexBuffer.bind();

    mBackgroundShader.setVertexBufferLayout(pixelVertexInfo.vertexBufferLayout);
    mBackgroundShader.bind();
    mBackgroundShader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());

    // FIXME: call this only if there is a change in the window screen
    renderer.clearScreen();
    renderer.drawElements(vertexArrayBuffer);
    renderer.render();
}
