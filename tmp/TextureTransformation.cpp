#include "TextureTransformation.h"

yaui::TextureTransformation::TextureTransformation(String name, yaui::TextureTransformationUpdateFunctionPointer pUpdateFunctionPointer) noexcept
    : name(std::move(name))
    , mpUpdateHandle(pUpdateFunctionPointer) {
}

void yaui::TextureTransformation::setUpdateHandle(yaui::TextureTransformationUpdateFunctionPointer pUpdateFunctionPointer) {
    mpUpdateHandle = pUpdateFunctionPointer;
}

void
yaui::TextureTransformation::update(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta) const {
    if(mpUpdateHandle) {
        mpUpdateHandle(renderer, registry, entity, delta);
    }
}
