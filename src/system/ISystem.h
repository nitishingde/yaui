#ifndef YAUI_SYSTEM_ISYSTEM_H
#define YAUI_SYSTEM_ISYSTEM_H


#include "Types.h"

namespace yaui::system {
    class ISystem {
    public:
        uint32 priorityRank = 0;

    public:
        virtual ~ISystem() = default;
        virtual void executeJob() = 0;
        [[nodiscard]] virtual String getClassName() const = 0;
        bool operator<(const ISystem &other) const;
    };
}


#endif //YAUI_SYSTEM_ISYSTEM_H
