#ifndef YAUI_SYSTEM_ISYSTEM_H
#define YAUI_SYSTEM_ISYSTEM_H


#include "Types.h"

namespace yaui::system {
    class ISystem {
    public:
        uint32 mPriorityRank = 0;

    public:
        virtual void executeJob() = 0;
        bool operator<(const ISystem &other) const;
    };
}


#endif //YAUI_SYSTEM_ISYSTEM_H
