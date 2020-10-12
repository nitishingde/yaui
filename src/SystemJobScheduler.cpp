#include "SystemJobScheduler.h"
#include "yaui.h"

static yaui::SystemJobScheduler* instance = nullptr;

yaui::SystemJobScheduler::SystemJobScheduler() {}

yaui::SystemJobScheduler *yaui::SystemJobScheduler::getInstance() {
    if(instance == nullptr) {
        instance = new SystemJobScheduler();
        instance->init();
    }

    return instance;
}

void yaui::SystemJobScheduler::init() {
    mSystems.emplace_back(new system::EventPollingSystem(0));
    mSystems.emplace_back(new system::BehaviourSystem(1));
    mSystems.emplace_back(new system::RenderingSystem(UINT32_MAX));
    std::sort(
        mSystems.begin(),
        mSystems.end(),
        [](const system::ISystem* pSys1, const system::ISystem *pSys2) {
            return pSys1->mPriorityRank < pSys2->mPriorityRank;
        }
    );
}

void yaui::SystemJobScheduler::executeJobs() {
    for(auto &system: mSystems) {
        system->executeJob();
    }
}
