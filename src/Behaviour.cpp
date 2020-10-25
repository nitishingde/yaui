#include "Behaviour.h"

yaui::Behaviour::Behaviour(String name, yaui::UpdateFunctionPointer pUpdateFunctionPointer) noexcept
    : name(std::move(name))
    , mpUpdateHandle(pUpdateFunctionPointer) {
}

void yaui::Behaviour::setUpdateHandle(yaui::UpdateFunctionPointer pUpdateFunctionPointer) {
    mpUpdateHandle = pUpdateFunctionPointer;
}

void
yaui::Behaviour::update(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta) const {
    if(mpUpdateHandle) {
        mpUpdateHandle(renderer, registry, entity, delta);
    }
}
