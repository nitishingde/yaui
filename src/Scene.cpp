#include "Scene.h"
#include "Director.h"
#include "RendererWrapper.h"

yaui::Scene::Scene(String name) noexcept : mName(std::move(name)) {
    mRegistry.set<RendererWrapper>(RendererWrapper(&Director::getInstance()->getRenderer()));
}

yaui::Scene::Scene(yaui::Scene &&other) noexcept
    : mName(std::move(other.mName))
    , mRegistry(std::move(other.mRegistry)) {
}

yaui::Scene& yaui::Scene::operator=(yaui::Scene &&other) noexcept {
    if(this != &other) {
        this->mName = std::move(other.mName);
        this->mRegistry = std::move(other.mRegistry);
    }
    return *this;
}

yaui::Scene::~Scene() {
    mRegistry.clear();
}

yaui::entity::Registry& yaui::Scene::getRegistry() {
    return mRegistry;
}
