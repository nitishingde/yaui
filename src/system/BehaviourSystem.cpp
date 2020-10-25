#include "BehaviourSystem.h"
#include <spdlog/spdlog.h>
#include "yaui.h"

yaui::system::BehaviourSystem::BehaviourSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
}

yaui::system::BehaviourSystem::~BehaviourSystem() {
    spdlog::info("DELETED| BehaviourSystem");
}

void yaui::system::BehaviourSystem::lockTexture(
    Renderer &renderer,
    entity::Registry &registry,
    const entity::Entity &entity,
    const float &delta
) {
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
    SDL_SetTextureBlendMode(texture2D.pTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(&renderer, texture2D.pTexture);
}

void yaui::system::BehaviourSystem::unlockTexture(
    Renderer &renderer,
    entity::Registry &registry,
    const entity::Entity &entity,
    const float &delta
) {
    // unlock texture from the renderer
    SDL_SetRenderTarget(&renderer, nullptr);
}

void yaui::system::BehaviourSystem::executeJob() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto &renderer = scene.getRenderer();
    auto delta = Director::getInstance()->getDelta();
    auto view = registry.view<component::BehaviourTraits>();
    auto shouldUpdateRenderPipeline = false;
    for(auto entity: view) {
        auto &behaviourTraits = view.get<component::BehaviourTraits>(entity);
        if(behaviourTraits.isTriggered) {
            lockTexture(renderer, registry, entity, delta);
            for(auto &behaviour: behaviourTraits.behaviours) {
                if(!behaviour.isEnabled) continue;
                behaviour.update(renderer, registry, entity, delta);
            }
            behaviourTraits.isTriggered = false;
            unlockTexture(renderer, registry, entity, delta);
            shouldUpdateRenderPipeline = true;
        }
    }

    if(shouldUpdateRenderPipeline) {
        auto renderingSystem = dynamic_cast<RenderingSystem*>(SystemJobScheduler::getInstance()->getSystem("RenderingSystem"));
        renderingSystem->updateRenderPipeline();
    }
}

yaui::String yaui::system::BehaviourSystem::getClassName() const {
    return "BehaviourSystem";
}
