#ifndef YAUI_SYSTEM_RENDERINGSYSTEM_H
#define YAUI_SYSTEM_RENDERINGSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class RenderingSystem: public ISystem {
    public:
        explicit RenderingSystem(uint32 priorityRank);
        void executeJob() override;
    };
}

#endif //YAUI_SYSTEM_RENDERINGSYSTEM_H
