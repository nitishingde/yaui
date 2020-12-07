#ifndef YAUI_SYSTEM_BEHAVIOURSYSTEM_H
#define YAUI_SYSTEM_BEHAVIOURSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class BehaviourSystem: public ISystem {
    public:
        explicit BehaviourSystem(uint32 priorityRank);
        ~BehaviourSystem() override;
        void executeJob() override;
        [[nodiscard]] String getClassName() const override;
    };
}


#endif //YAUI_SYSTEM_BEHAVIOURSYSTEM_H
