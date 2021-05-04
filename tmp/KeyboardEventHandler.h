#ifndef YAUI_KEYBOARDEVENTHANDLER_H
#define YAUI_KEYBOARDEVENTHANDLER_H


#include "IEventHandler.h"

namespace yaui {
    class KeyboardEventHandler: public IEventHandler {
    public:
        bool isEventTypeSupported(const EventType &eventType) override;
        void handleEvents() override;
    };
}

#endif //YAUI_KEYBOARDEVENTHANDLER_H
