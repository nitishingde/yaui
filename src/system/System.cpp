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
    vertexBuffer.setData(quadVertices.data(), quadVertices.size()*sizeof(std::remove_reference<decltype(quadVertices)>::type::value_type));
    vertexBuffer.bind();

    gles2::VertexArrayBuffer vertexArrayBuffer(vertexArray);
    vertexArrayBuffer.bind();

    mBackgroundShader.setVertexBufferLayout(quadVertexInfo.vertexBufferLayout);
    mBackgroundShader.bind();
    mBackgroundShader.setUniformMatrix4f("uMVP", renderer.getMVP_Matrix());

    // FIXME: call this only if there is a change in the window screen
    renderer.clearScreen();
    renderer.drawElements(vertexArrayBuffer);
    renderer.render();
}
