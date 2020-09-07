#include "Director.h"
#include "SDL.h"
#include "SDL_ttf.h"

yaui::system::Director* instance = nullptr;

yaui::system::Director::Director() {
    mIsInitialised = false;
}

yaui::system::Director::~Director() {}

yaui::system::Director *yaui::system::Director::getInstance() {
    if(!instance) {
        instance = new Director();
    }

    return instance;
}

bool yaui::system::Director::init() {
    if(this->mIsInitialised) return true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    if(TTF_Init() < 0) {
        return false;
    }

    return this->mIsInitialised = true;
}
