#include <algorithm>
#include "SystemJobScheduler.h"

yaui::system::SystemJobScheduler::SystemJobScheduler() {
    mSystems.emplace_back(std::make_shared<RenderingBackgroundSystem>(1));
    std::sort(mSystems.begin(), mSystems.end());
}

void yaui::system::SystemJobScheduler::executeJobs(entt::registry &registry, gles2::Renderer &renderer) {
    for(auto &pSystem: mSystems) {
        pSystem->executeJob(registry, renderer);
    }
}
