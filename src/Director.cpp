#include "Director.h"
#include <iostream>
#include "SystemJobScheduler.h"
#include "system/RenderingSystem.h"

static yaui::Director* instance = nullptr;

yaui::Director::Director() = default;

yaui::Director::~Director() {
    for(auto pScene: mSceneStack) {
        delete pScene;
    }
    mSceneStack.clear();
    delete SystemJobScheduler::getInstance();

    if(mpRenderer) {
        SDL_DestroyRenderer(mpRenderer);
        std::cout<<"DELETED| Renderer\n";
    }

    if(mpWindow) {
        SDL_DestroyWindow(mpWindow);
        std::cout<<"DELETED| Window\n";
    }

    if(IMG_Init(0)&IMG_INIT_PNG) {
        IMG_Quit();
        std::cout<<"DELETED| IMG lib\n";
    }

    if(TTF_WasInit()) {
        TTF_Quit();
        std::cout<<"DELETED| TTF lib\n";
    }

    if(SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_Quit();
        std::cout<<"DELETED| SDL2 lib\n";
    }

    instance = nullptr;
}

bool yaui::Director::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    std::cout<<"INITIALISED| SDL lib\n";
    if(TTF_Init() < 0) return false;
    std::cout<<"INITIALISED| TTF lib\n";
    if(IMG_Init(IMG_INIT_PNG) < 0) return false;
    std::cout<<"INITIALISED| IMG lib\n";

    mpWindow = SDL_CreateWindow(
        "YAUI",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_RESIZABLE
    );
    if(mpWindow == nullptr) return false;
    std::cout<<"INITIALISED| Window\n";

    mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
    if(mpRenderer == nullptr) return false;
    std::cout<<"INITIALISED| Renderer\n";

    return true;
}

yaui::Director *yaui::Director::getInstance() {
    if(instance == nullptr) {
        instance = new Director();
        if(!instance->init()) return nullptr;
    }
    return instance;
}

void yaui::Director::disableStats() {
    auto renderingSystem = dynamic_cast<system::RenderingSystem*>(SystemJobScheduler::getInstance()->getSystem("RenderingSystem"));
    if(renderingSystem) renderingSystem->displayStats(false);
}

void yaui::Director::enableStats() {
    auto renderingSystem = dynamic_cast<system::RenderingSystem*>(SystemJobScheduler::getInstance()->getSystem("RenderingSystem"));
    if(renderingSystem) renderingSystem->displayStats(true);
}

float yaui::Director::getDelta() const {
    return mDelta;
}

yaui::Renderer& yaui::Director::getRenderer() const {
    return *mpRenderer;
}

yaui::Scene& yaui::Director::getScene() const {
    return *mSceneStack.back();
}

yaui::Size yaui::Director::getWindowSize() const {
    int32 width, height;
    SDL_GetWindowSize(mpWindow, &width, &height);
    return Size {uint32(height), uint32(width)};
}

void yaui::Director::popScene() {
    delete mSceneStack.back();
    mSceneStack.pop_back();
}

void yaui::Director::pushScene(yaui::Scene *pScene) {
    mSceneStack.emplace_back(pScene);
}

void yaui::Director::setFPS(yaui::uint32 fps) {
    mFps = fps;
}

void yaui::Director::quit() {
    mEngineIgnitionOn = false;
}

void yaui::Director::run() {
    int64 ticksPerFrame = 1000/mFps;
    mDelta = ticksPerFrame;
    while(mEngineIgnitionOn) {
        auto start = SDL_GetTicks();
        SystemJobScheduler::getInstance()->executeJobs();
        auto jobExecutionTime = SDL_GetTicks()-start;
        if(jobExecutionTime < ticksPerFrame) {
            // add time delay to maintain the fps
            SDL_Delay(ticksPerFrame-jobExecutionTime);
            mDelta = ticksPerFrame;
        } else {
            mDelta = jobExecutionTime;
        }
    }
    std::cout<<"EVENT| Escape Pressed\n";
    delete this;
}
