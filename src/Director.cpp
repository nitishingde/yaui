#include "Director.h"

static yaui::Director* instance = nullptr;

yaui::Director::~Director() {
    SDL_Quit();
}

yaui::Director *yaui::Director::getInstance() {
    if(instance == nullptr) {
        instance = new Director();
        if(!instance->init()) return nullptr;
    }
    return instance;
}

bool yaui::Director::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    mWindows.emplace_back(std::make_shared<gles2::Window>("YAUI OpenGL ES 2.0"));
    return true;
}

void yaui::Director::quit() {
    delete instance;
    instance = nullptr;
}

void yaui::Director::pushScene(std::shared_ptr<Scene> pScene) {
    mWindows[0]->setName(pScene->getName().c_str());
    pScene->setRenderer(gles2::Renderer(mWindows[0]));
    mSceneStack.emplace_back(std::move(pScene));
}

void yaui::Director::popScene() {
    mSceneStack.pop_back();
}
