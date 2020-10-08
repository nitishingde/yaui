#include "Director.h"
#include "SystemJobScheduler.h"
#include <iostream>

static yaui::Director* instance = nullptr;

yaui::Director::Director() = default;

yaui::Director::~Director() {
    mRegistry.clear();
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
    delete SystemJobScheduler::getInstance();
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
        0
    );
    if(mpWindow == nullptr) return false;
    std::cout<<"INITIALISED| Window\n";

    mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_SOFTWARE);
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

yaui::entity::Registry& yaui::Director::getRegistry() {
    return mRegistry;
}

yaui::Renderer& yaui::Director::getRenderer() {
    return *mpRenderer;
}

void yaui::Director::run() {
    while(true) {
        SystemJobScheduler::getInstance()->executeJobs();
        SDL_Delay(33);
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_KEYDOWN and event.key.keysym.sym == SDLK_ESCAPE) {
                std::cout<<"EVENT| Escape Pressed\n";
                delete this;
                return;
            }
        }
    }
}
