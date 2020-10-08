#include "RenderingSystem.h"
#include "Director.h"
#include "component/Texture2D.h"
#include "component/Transform.h"

yaui::system::RenderingSystem::RenderingSystem(yaui::uint32 priorityRank) {
    ISystem::mPriorityRank = priorityRank;
}

void yaui::system::RenderingSystem::executeJob() {
    auto &registry = Director::getInstance()->getRegistry();
    auto &renderer = Director::getInstance()->getRenderer();
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
