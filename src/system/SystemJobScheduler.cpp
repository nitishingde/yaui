#include <algorithm>
#include "SystemJobScheduler.h"

yaui::system::SystemJobScheduler::SystemJobScheduler() {
    mSystems.emplace_back(std::make_shared<RenderingBackgroundSystem>(1));
    mSystems.emplace_back(std::make_shared<RenderingTextureSystem>(2));
    std::sort(mSystems.begin(), mSystems.end());
}

void yaui::system::SystemJobScheduler::executeJobs(entt::registry &registry, gles2::Renderer &renderer) {
    // FIXME: call this only if there is a change in the window screen
    renderer.clearScreen();

    for(auto &pSystem: mSystems) {
        pSystem->executeJob(registry, renderer);
    }

    renderer.render();
}
