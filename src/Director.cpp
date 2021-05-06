#include "Director.h"
#include "system/SystemJobScheduler.h"

static yaui::Director* spInstance = nullptr;

yaui::Director::~Director() {
    SDL_Quit();
}

yaui::Director *yaui::Director::getInstance() {
    if(spInstance == nullptr) {
        spInstance = new Director();
        if(!spInstance->init()) return nullptr;
    }
    return spInstance;
}

bool yaui::Director::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    mWindows.emplace_back(std::make_shared<gles2::Window>("YAUI OpenGL ES 2.0"));
    return true;
}

void yaui::Director::run() {
    uint32 ticksPerFrame = 1000/mFps;
    mDelta = ticksPerFrame;
    while(mEngineIgnitionOn) {
        auto start = SDL_GetTicks();
        auto pScene = mSceneStack.back();
        // FIXME: MOve this to event handling system
        for(SDL_Event event; SDL_PollEvent(&event);) {
            if(event.type == SDL_QUIT) stop();
        }
        system::SystemJobScheduler::getInstance()->executeJobs(pScene->getRegistry(), pScene->getRenderer());
        auto jobExecutionTime = SDL_GetTicks()-start;
        if(jobExecutionTime < ticksPerFrame) {
            // add time delay to maintain the fps
            SDL_Delay(ticksPerFrame-jobExecutionTime);
            mDelta = ticksPerFrame;
        } else {
            mDelta = jobExecutionTime;
        }
    }
    delete this;
}

void yaui::Director::stop() {
    mEngineIgnitionOn = false;
}

void yaui::Director::quit() {
    mEngineIgnitionOn = false;
    delete spInstance;
    spInstance = nullptr;
}

void yaui::Director::pushScene(const std::shared_ptr<Scene> &pScene) {
    mWindows[0]->setName(pScene->getName().c_str());
    pScene->setRenderer(gles2::Renderer(mWindows[0]));
    mSceneStack.emplace_back(pScene);
}

void yaui::Director::popScene() {
    mSceneStack.pop_back();
}

void yaui::Director::setFPS(yaui::uint32 fps) {
    mFps = fps;
}
