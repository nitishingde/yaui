#include "RenderingSystem.h"
#include "Director.h"
#include "component/Texture2D.h"
#include "component/Transform.h"

yaui::system::RenderingSystem::RenderingSystem(yaui::uint32 priorityRank) {
    ISystem::mPriorityRank = priorityRank;
}

void yaui::system::RenderingSystem::executeJob() {
    auto &reg = Director::getInstance()->getRegistry();
    auto pRenderer = Director::getInstance()->getRenderer();
    SDL_SetRenderTarget(pRenderer, nullptr);
    SDL_SetRenderDrawColor(pRenderer, 64, 64, 64, 255);
    SDL_RenderClear(pRenderer);
    reg.view<component::Texture2D, component::Transform>().each(
        [pRenderer](component::Texture2D &texture2D, component::Transform transform) {
            SDL_RenderCopy(pRenderer, texture2D.pTexture, nullptr, &transform.viewPort);
        }
    );
    SDL_RenderPresent(pRenderer);
}
