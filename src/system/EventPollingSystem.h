#ifndef YAUI_SYSTEM_EVENTPOLLINGSYSTEM_H
#define YAUI_SYSTEM_EVENTPOLLINGSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class EventPollingSystem: public ISystem {
    private:
        void handleMouseEvents(const Event &event);
    public:
        explicit EventPollingSystem(uint32 priorityRank);
        void executeJob() override;
    };
}


#endif //YAUI_SYSTEM_EVENTPOLLINGSYSTEM_H
