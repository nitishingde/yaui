#ifndef YAUI_TEXTINPUTEVENTHANDLER_H
#define YAUI_TEXTINPUTEVENTHANDLER_H


#include "IEventHandler.h"

namespace yaui {
    class TextInputEventHandler: public IEventHandler {
    // FIXME
    // Register TextInputListeners rather than iterating on all of them
    public:
        bool isEventTypeSupported(const EventType &eventType) override;
        void handleEvents() override;
    };
}


#endif //YAUI_TEXTINPUTEVENTHANDLER_H
