#include "Scene.h"

#include <utility>
#include "Director.h"
#include "Types.h"

yaui::Scene::Scene(String name) noexcept
    : mName(std::move(name))
    , mpRenderer(&Director::getInstance()->getRenderer()) {
}

yaui::Scene::Scene(yaui::Scene &&other) noexcept
    : mName(std::move(other.mName))
    , mRegistry(std::move(other.mRegistry))
    , mpRenderer(other.mpRenderer) {
    other.mpRenderer = nullptr;
}

yaui::Scene& yaui::Scene::operator=(yaui::Scene &&other) noexcept {
    if(this != &other) {
        this->mName = std::move(other.mName);
        this->mRegistry = std::move(other.mRegistry);
        this->mpRenderer = other.mpRenderer;
        other.mpRenderer = nullptr;
    }
    return *this;
}

yaui::Scene::~Scene() {
    mRegistry.clear();
    mpRenderer = nullptr;
}

yaui::entity::Registry& yaui::Scene::getRegistry() {
    return mRegistry;
}

yaui::Renderer& yaui::Scene::getRenderer() const {
    return *mpRenderer;
}
