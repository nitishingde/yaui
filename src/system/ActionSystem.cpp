#include "ActionSystem.h"
#include <spdlog/spdlog.h>
#include "component/Components.h"
#include "Director.h"

yaui::system::ActionSystem::ActionSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
}

yaui::system::ActionSystem::~ActionSystem() {
    spdlog::info("DELETED| ActionSystem");
}

void yaui::system::ActionSystem::executeJob() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto delta = Director::getInstance()->getDelta();
    auto view = registry.view<component::ActionItems>();
    for(auto &entity: view) {
        auto &actionableItems = view.get(entity).actions;
        // carry out and delete unwanted actions
        size_t finalSize = actionableItems.size();
        for(int32 index = 0, freeSlot = -1; index < actionableItems.size(); ++index) {
            if(!actionableItems[index].update(registry, entity, delta)) {
                finalSize--;
                if(freeSlot == -1) freeSlot = index;
            } else if(freeSlot != -1) {
                actionableItems[freeSlot] = actionableItems[index];
                freeSlot++;
            }
        }
        actionableItems.resize(finalSize);
    }
}

yaui::String yaui::system::ActionSystem::getClassName() const {
    return YAUI_TO_STRING(ActionSystem);
}
