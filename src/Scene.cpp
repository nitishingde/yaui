#include "Scene.h"

yaui::Scene::Scene(const char *pName) noexcept
    : mName(pName) {
    mRegistryStack.emplace_back(entt::registry());
}

yaui::Scene::Scene(yaui::Scene &&other) noexcept
    : mName(std::move(other.mName))
    , mRegistryStack(std::move(other.mRegistryStack)) {
//    , mRenderers(std::move(other.mRenderers)) {//FIXME

}

yaui::Scene& yaui::Scene::operator=(yaui::Scene &&other) noexcept {
    if(this != &other) {
        mName = std::move(other.mName);
        mRegistryStack = std::move(other.mRegistryStack);
        mRenderers = std::move(other.mRenderers);
    }
    return *this;
}

std::string yaui::Scene::getName() const {
    return mName;
}

entt::registry& yaui::Scene::getRegistry(yaui::uint32 idx) {
    return mRegistryStack[0];
}

yaui::gles2::Renderer& yaui::Scene::getRenderer(yaui::uint32 idx) {
    return mRenderers[0];
}

void yaui::Scene::setRenderer(gles2::Renderer &&renderer) {
    mRenderers.emplace_back(std::move(renderer));
}
