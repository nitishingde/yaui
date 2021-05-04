#include "BehaviourSystem.h"
#include "Director.h"
#include "component/Components.h"
#include "LoggerConstants.h"

yaui::system::BehaviourSystem::BehaviourSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    spdlog::info("{} {}", Logger::kConstructed, BehaviourSystem::getClassName());
}

yaui::system::BehaviourSystem::~BehaviourSystem() {
    spdlog::info("{} {}", Logger::kDestructed, BehaviourSystem::getClassName());
}

void yaui::system::BehaviourSystem::executeJob() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto delta = Director::getInstance()->getDelta();
    auto view = registry.view<component::BehaviourTraits>();
    for(auto &entity: view) {
        for(auto &behaviour: view.get(entity).behaviours) {
            behaviour.update(registry, entity, delta);
        }
    }
}

yaui::String yaui::system::BehaviourSystem::getClassName() const {
    return YAUI_TO_STRING(yaui::system::BehaviourSystem);
}
