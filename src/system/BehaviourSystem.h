#ifndef YAUI_SYSTEM_BEHAVIOURSYSTEM_H
#define YAUI_SYSTEM_BEHAVIOURSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class BehaviourSystem: public ISystem {
    private:
        void lockTexture(entity::Registry &registry, const entity::Entity &entity, const float &delta);
        void unlockTexture(entity::Registry &registry, const entity::Entity &entity, const float &delta);
    public:
        explicit BehaviourSystem(uint32 priorityRank);
        void executeJob() override;
    };
}


#endif //YAUI_SYSTEM_BEHAVIOURSYSTEM_H
