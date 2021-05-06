#include <algorithm>
#include "SystemJobScheduler.h"

static yaui::system::SystemJobScheduler *spInstance = nullptr;

void yaui::system::SystemJobScheduler::init() {
    mSystems.emplace_back(std::make_shared<RenderingBackgroundSystem>(1));
    std::sort(mSystems.begin(), mSystems.end());
}

yaui::system::SystemJobScheduler::~SystemJobScheduler() {
    delete spInstance;
    spInstance = nullptr;
}

yaui::system::SystemJobScheduler* yaui::system::SystemJobScheduler::getInstance() {
    if(spInstance == nullptr) {
        spInstance = new SystemJobScheduler();
        spInstance->init();
    }
    return spInstance;
}

void yaui::system::SystemJobScheduler::executeJobs(entt::registry &registry, gles2::Renderer &renderer) {
    for(auto &pSystem: mSystems) {
        pSystem->executeJob(registry, renderer);
    }
}
