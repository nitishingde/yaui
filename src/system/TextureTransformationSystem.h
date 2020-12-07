#ifndef YAUI_SYSTEM_TEXTURETRANSFORMATIONSYSTEM_H
#define YAUI_SYSTEM_TEXTURETRANSFORMATIONSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class TextureTransformationSystem: public ISystem {
    private:
        void lockTexture(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, const float &delta);
        void unlockTexture(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, const float &delta);
    public:
        explicit TextureTransformationSystem(uint32 priorityRank);
        ~TextureTransformationSystem() override;
        void executeJob() override;
        [[nodiscard]] String getClassName() const override;
    };
}


#endif //YAUI_SYSTEM_TEXTURETRANSFORMATIONSYSTEM_H
