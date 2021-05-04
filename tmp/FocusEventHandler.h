#ifndef YAUI_FOCUSEVENTHANDLER_H
#define YAUI_FOCUSEVENTHANDLER_H


#include "IEventHandler.h"

namespace yaui {
    class FocusEventHandler: public IEventHandler {
    public:
        bool isEventTypeSupported(const EventType &eventType) override;
        void handleEvents() override;
    };
}


#endif //YAUI_FOCUSEVENTHANDLER_H
