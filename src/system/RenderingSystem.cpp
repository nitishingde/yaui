#include "RenderingSystem.h"
#include "LoggerConstants.h"
#include "yaui.h"

yaui::system::RenderingSystem::RenderingSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    mpFont = TTF_OpenFont("resources/open-sans/OpenSans-Regular.ttf", 32);
    spdlog::info("{} {}", Logger::kConstructed, RenderingSystem::getClassName());
}

yaui::system::RenderingSystem::~RenderingSystem() {
    if(mpFont) TTF_CloseFont(mpFont);
    mpFont = nullptr;
    if(mpStatsTexture) SDL_DestroyTexture(mpStatsTexture);
    mpStatsTexture = nullptr;
    spdlog::info("{} {}", Logger::kDestructed, RenderingSystem::getClassName());
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
        spdlog::info("{} FPS = {:.3f}", Logger::kStats, fps);
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
    if(!mShouldUpdateRenderPipeline and !mDisplayStats) return;
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto &renderer = scene.getRenderer();
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
    mShouldUpdateRenderPipeline = false;
}

yaui::String yaui::system::RenderingSystem::getClassName() const {
    return YAUI_TO_STRING(yaui::system::RenderingSystem);
}

void yaui::system::RenderingSystem::displayStats(bool displayStats) {
    mDisplayStats = displayStats;
}

void yaui::system::RenderingSystem::updateRenderPipeline() {
    mShouldUpdateRenderPipeline = true;
}
