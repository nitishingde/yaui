#ifndef YAUI_IEVENTHANDLER_H
#define YAUI_IEVENTHANDLER_H


#include "Types.h"

namespace yaui {
    class IEventHandler {
    protected:
        ArrayList<Event> mEventQueue;

    protected:
        virtual void handleEventListeners(ArrayList<EventHandlerFunctionPointer> &eventListeners, entity::Registry &registry, const entity::Entity &entity, const Event &event);
    public:
        virtual ~IEventHandler() = default;
        void enqueueEvent(const Event &event);
        virtual bool isEventTypeSupported(const EventType &eventType) = 0;
        virtual void handleEvents() = 0;
    };
}


#endif //YAUI_IEVENTHANDLER_H
