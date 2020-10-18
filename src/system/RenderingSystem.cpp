#include "RenderingSystem.h"
#include <iostream>
#include "yaui.h"

yaui::system::RenderingSystem::RenderingSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
}

yaui::system::RenderingSystem::~RenderingSystem() {
    std::cout<<"Deleted| RenderingSystem\n";
}

void yaui::system::RenderingSystem::executeJob() {
    auto &registry = Director::getInstance()->getScene().getRegistry();
    auto &renderer = registry.ctx<RendererWrapper>().getRenderer();
    SDL_SetRenderTarget(&renderer, nullptr);
    SDL_SetRenderDrawColor(&renderer, 64, 64, 64, 255);
    SDL_RenderClear(&renderer);
    registry.view<component::Texture2D, component::Transform>().each(
        [&renderer](component::Texture2D &texture2D, component::Transform transform) {
            SDL_RenderCopy(&renderer, texture2D.pTexture, nullptr, &transform.viewPort);
        }
    );
    SDL_RenderPresent(&renderer);
}

yaui::String yaui::system::RenderingSystem::getClassName() const {
    return "RenderingSystem";
}
