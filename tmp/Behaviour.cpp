#include "Behaviour.h"

yaui::Behaviour::Behaviour(yaui::String name, yaui::BehaviourUpdateFunctionPointer pUpdateFunctionPointer) noexcept
    : name(std::move(name))
    , mpUpdateHandle(pUpdateFunctionPointer) {

}

void yaui::Behaviour::setUpdateHandle(yaui::BehaviourUpdateFunctionPointer pUpdateFunctionPointer) {
    mpUpdateHandle = pUpdateFunctionPointer;
}

void
yaui::Behaviour::update(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, float delta) const {
    if(mpUpdateHandle) {
        mpUpdateHandle(registry, entity, delta);
    }
}
