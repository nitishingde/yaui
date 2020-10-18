#include "BehaviourSystem.h"
#include <iostream>
#include "yaui.h"

yaui::system::BehaviourSystem::BehaviourSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
}

yaui::system::BehaviourSystem::~BehaviourSystem() {
    std::cout<<"Deleted| BehaviourSystem\n";
}

void
yaui::system::BehaviourSystem::lockTexture(entity::Registry &registry, const entity::Entity &entity, const float &delta) {
    auto &renderer = registry.ctx<RendererWrapper>().getRenderer();
    auto [texture2D, transform] = registry.get<component::Texture2D, component::Transform>(entity);
    // delete old texture and create a new one
    if(texture2D.pTexture) {
        SDL_DestroyTexture(texture2D.pTexture);
        texture2D.pTexture = nullptr;
    }
    texture2D.pTexture = SDL_CreateTexture(
        &renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        transform.viewPort.w,
        transform.viewPort.h
    );
    // lock texture to the renderer
    SDL_SetRenderTarget(&renderer, texture2D.pTexture);
}

void
yaui::system::BehaviourSystem::unlockTexture(entity::Registry &registry, const entity::Entity &entity, const float &delta) {
    // unlock texture from the renderer
    auto &renderer = registry.ctx<RendererWrapper>().getRenderer();
    SDL_SetRenderTarget(&renderer, nullptr);
}

void yaui::system::BehaviourSystem::executeJob() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto delta = Director::getInstance()->getDelta();
    auto view = registry.view<component::BehaviourTraits>();
    for(auto entity: view) {
        auto &behaviourTraits = view.get<component::BehaviourTraits>(entity);
        if(!behaviourTraits.isUpdated) {
            lockTexture(registry, entity, delta);
            for(auto &behaviour: behaviourTraits.behaviours) {
                behaviour.update(registry, entity, delta);
            }
            behaviourTraits.isUpdated = true;
            unlockTexture(registry, entity, delta);
        }
    }
}

yaui::String yaui::system::BehaviourSystem::getClassName() const {
    return "BehaviourSystem";
}
