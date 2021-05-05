#include "Scene.h"

yaui::Scene::Scene(const char *pName) noexcept
    : mName(pName) {
    mRegistryStack.emplace_back(entt::registry{});
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
