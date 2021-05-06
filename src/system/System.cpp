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
    auto &pixelVertices = registry.ctx<gles2::PixelVertices>();
    auto &vertices = pixelVertices.vertexData;
    gles2::VertexArrayBuffer va;
    auto &vertexArray = va.getVertexArray();

    auto view = registry.view<component::Transform>();
    uint32 i = 0;
    for(auto entity: view) {
        auto entityIdx = static_cast<uint32>(entity)<<2;
        auto &viewPort = view.get(entity).viewPort;
        auto &colour = view.get(entity).colour;
        vertices[entityIdx+0].colour = colour;
        vertices[entityIdx+0].position = {viewPort.x, viewPort.y};
        vertices[entityIdx+1].colour = colour;
        vertices[entityIdx+1].position = {viewPort.x, viewPort.y + viewPort.w};
        vertices[entityIdx+2].colour = colour;
        vertices[entityIdx+2].position = {viewPort.x + viewPort.z, viewPort.y + viewPort.w};
        vertices[entityIdx+3].colour = colour;
        vertices[entityIdx+3].position = {viewPort.x + viewPort.z, viewPort.y};
        vertexArray.insert(vertexArray.end(), {entityIdx+0, entityIdx+1, entityIdx+2, entityIdx+0, entityIdx+2, entityIdx+3});
    }

    va.bind();

    gles2::VertexBuffer vb(vertices.data(), sizeof(gles2::PixelVertex), vertices.size(), pixelVertices.bufferLayout);
    vb.bind();

    mBackgroundShader.setBufferLayout(pixelVertices.bufferLayout);
    mBackgroundShader.bind();
    mBackgroundShader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());

    renderer.drawElements(va);
    renderer.render();
}
