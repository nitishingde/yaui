#include "RenderingSystem.h"
#include <iostream>
#include "yaui.h"

yaui::system::RenderingSystem::RenderingSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    mpFont = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 32);
}

yaui::system::RenderingSystem::~RenderingSystem() {
    if(mpFont) TTF_CloseFont(mpFont);
    mpFont = nullptr;
    if(mpStatsTexture) SDL_DestroyTexture(mpStatsTexture);
    mpStatsTexture = nullptr;
    std::cout<<"Deleted| RenderingSystem\n";
}

void yaui::system::RenderingSystem::displayStats() {
    auto pDirector = Director::getInstance();
    float fps = 1000.f/pDirector->getDelta();
    auto &renderer = pDirector->getRenderer();
    if(0.01f < std::abs(fps-mFps) or mpStatsTexture == nullptr) {
        mFps = fps;
        auto pSurface = TTF_RenderText_Blended(
            mpFont,
            ("FPS: "+std::to_string(int(fps))+"  ").c_str(),
            Colour {255, 0, 0, 255}
        );
        std::cout<<"FPS: "<<fps<<'\n';
        if(mpStatsTexture) SDL_DestroyTexture(mpStatsTexture);
        mpStatsTexture = SDL_CreateTextureFromSurface(&renderer, pSurface);
        SDL_FreeSurface(pSurface);
    }

    int width, height;
    SDL_QueryTexture(mpStatsTexture, nullptr, nullptr, &width, &height);
    auto winSize = pDirector->getWindowSize();
    ViewPort viewPort {int32(winSize.width)-width, int32(winSize.height)-height, width, height};
    SDL_RenderCopy(&renderer, mpStatsTexture, nullptr, &viewPort);
}

void yaui::system::RenderingSystem::executeJob() {
    auto &registry = Director::getInstance()->getScene().getRegistry();
    auto &renderer = registry.ctx<RendererWrapper>().getRenderer();
    SDL_SetRenderTarget(&renderer, nullptr);
    SDL_SetRenderDrawBlendMode(&renderer, SDL_BlendMode::SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(&renderer, 64, 64, 64, 255);
    SDL_RenderClear(&renderer);
    registry.view<component::Texture2D, component::Transform>().each(
        [&renderer](component::Texture2D &texture2D, component::Transform transform) {
            SDL_RenderCopy(&renderer, texture2D.pTexture, nullptr, &transform.viewPort);
        }
    );
    if(mDisplayStats) displayStats();
    SDL_RenderPresent(&renderer);
}

yaui::String yaui::system::RenderingSystem::getClassName() const {
    return "RenderingSystem";
}

void yaui::system::RenderingSystem::displayStats(bool displayStats) {
    mDisplayStats = displayStats;
}
