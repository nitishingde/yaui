#ifndef YAUI_SYSTEM_SYSTEM_H
#define YAUI_SYSTEM_SYSTEM_H


#include "ISystem.h"
#include "IEventHandler.h"

namespace yaui::system {
    class EventSystem: public ISystem {
    private:
        ArrayList<IEventHandler*> mEventHandlers;

    private:
        void pollEvents();
    public:
        explicit EventSystem(uint32 priorityRank);
        void executeJob() override;
    };
}


#endif //YAUI_SYSTEM_EVENTSYSTEM_H
