#ifndef YAUI_TEXTURETRANSFORMATION_H
#define YAUI_TEXTURETRANSFORMATION_H


#include "Types.h"

namespace yaui {
    class TextureTransformation {
    private:
        TextureTransformationUpdateFunctionPointer mpUpdateHandle = nullptr;
    public:
        String name;
        bool isEnabled = true;

    public:
        explicit TextureTransformation(String name, TextureTransformationUpdateFunctionPointer pUpdateFunctionPointer = nullptr) noexcept;
        void setUpdateHandle(TextureTransformationUpdateFunctionPointer pUpdateFunctionPointer);
        void update(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta) const;
    };
}


#endif //YAUI_TEXTURETRANSFORMATION_H
