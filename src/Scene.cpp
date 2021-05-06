#include "Scene.h"
#include "gles2/Buffer.h"

yaui::Scene::Scene(const char *pName) noexcept
    : mName(pName) {
    entt::registry registry;
    registry.set<gles2::PixelVertices>(gles2::PixelVertices{
        gles2::BufferLayout{
            {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(gles2::PixelVertex, position)},
            {"aColour", 1, 4, GL_FLOAT, GL_FALSE, offsetof(gles2::PixelVertex, colour)}
        },
        gles2::VertexBuffer(),
        std::vector<gles2::PixelVertex>(4096)
    });
    mRegistryStack.emplace_back(std::move(registry));
}

std::string yaui::Scene::getName() const {
    return mName;
}

entt::registry& yaui::Scene::getRegistry(yaui::uint32 idx) {
    return mRegistryStack.front();
}

yaui::gles2::Renderer& yaui::Scene::getRenderer(yaui::uint32 idx) {
    return mRenderers.front();
}

void yaui::Scene::setRenderer(gles2::Renderer &&renderer) {
    mRenderers.emplace_back(std::move(renderer));
}
