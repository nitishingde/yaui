#include "Scene.h"
#include "gles2/Buffer.h"

yaui::Scene::Scene(const char *pName) noexcept
    : mName(pName) {
    entt::registry registry;
    registry.set<gles2::PixelVertexInfo>(gles2::PixelVertexInfo{
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
