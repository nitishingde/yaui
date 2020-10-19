#include "SystemJobScheduler.h"
#include "yaui.h"

static yaui::SystemJobScheduler* instance = nullptr;

yaui::SystemJobScheduler::~SystemJobScheduler() {
    mSystemStore.clear();
    for(auto pSystem: mSystems) {
        delete pSystem;
    }
    mSystems.clear();
    instance = nullptr;
}

yaui::SystemJobScheduler *yaui::SystemJobScheduler::getInstance() {
    if(instance == nullptr) {
        instance = new SystemJobScheduler();
        instance->init();
    }

    return instance;
}

void yaui::SystemJobScheduler::init() {
    mSystems.emplace_back(new system::EventSystem(0));
    mSystems.emplace_back(new system::ActionSystem(UINT32_MAX-2));
    mSystems.emplace_back(new system::BehaviourSystem(UINT32_MAX-1));
    mSystems.emplace_back(new system::RenderingSystem(UINT32_MAX));

    for(auto &system: mSystems) {
        mSystemStore[system->getClassName()] = system;
    }

    std::sort(
        mSystems.begin(),
        mSystems.end(),
        [](const system::ISystem *pSys1, const system::ISystem *pSys2) {
            return pSys1->priorityRank < pSys2->priorityRank;
        }
    );
}

void yaui::SystemJobScheduler::executeJobs() {
    for(auto &system: mSystems) {
        system->executeJob();
    }
}

yaui::system::ISystem* yaui::SystemJobScheduler::getSystem(const String &systemName) const {
    return mSystemStore.at(systemName);
}
