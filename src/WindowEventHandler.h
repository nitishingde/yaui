#ifndef YAUI_WINDOWEVENTHANDLER_H
#define YAUI_WINDOWEVENTHANDLER_H


#include "IEventHandler.h"

namespace yaui {
    class WindowEventHandler: public IEventHandler {
    public:
        bool isEventTypeSupported(const EventType &eventType) override;
        void handleEvents() override;
    };
}


#endif //YAUI_WINDOWEVENTHANDLER_H
