#ifndef YAUI_SYSTEM_ACTIONSYSTEM_H
#define YAUI_SYSTEM_ACTIONSYSTEM_H


#include "ISystem.h"

namespace yaui::system{
    class ActionSystem: public ISystem {
    public:
        explicit ActionSystem(uint32 priorityRank);
        ~ActionSystem() override;
        void executeJob() override;
        [[nodiscard]] String getClassName() const override;
    };
}


#endif //YAUI_SYSTEM_ACTIONSYSTEM_H
