#include "Behaviour.h"

yaui::Behaviour::Behaviour(String name, yaui::UpdateFunctionPointer pUpdateFunctionPointer) noexcept
    : name(std::move(name))
    , mpUpdateHandle(pUpdateFunctionPointer) {
}

void yaui::Behaviour::setUpdateHandle(yaui::UpdateFunctionPointer pUpdateFunctionPointer) {
    mpUpdateHandle = pUpdateFunctionPointer;
}

void
yaui::Behaviour::update(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, float delta) const {
    if(mpUpdateHandle) {
        mpUpdateHandle(registry, entity, delta);
    }
}
