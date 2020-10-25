#ifndef YAUI_SYSTEM_BEHAVIOURSYSTEM_H
#define YAUI_SYSTEM_BEHAVIOURSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class BehaviourSystem: public ISystem {
    private:
        void lockTexture(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, const float &delta);
        void unlockTexture(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, const float &delta);
    public:
        explicit BehaviourSystem(uint32 priorityRank);
        ~BehaviourSystem() override;
        void executeJob() override;
        [[nodiscard]] String getClassName() const override;
    };
}


#endif //YAUI_SYSTEM_BEHAVIOURSYSTEM_H
