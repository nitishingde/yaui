#ifndef YAUI_MOUSEEVENTHANDLER_H
#define YAUI_MOUSEEVENTHANDLER_H


#include "IEventHandler.h"

namespace yaui {
    class MouseEventHandler: public IEventHandler {
    private:
        ArrayList<uint32> mValidEventTypes {
            EventType::SDL_MOUSEBUTTONDOWN,
            EventType::SDL_MOUSEBUTTONUP,
            EventType::SDL_MOUSEMOTION,
            EventType::SDL_MOUSEWHEEL
        };

    private:
        entity::Entity getTargetEntity(const Vec2 &position, entity::Registry &registry, entity::Entity previousTargetedEntity = entity::null);
        void pollEvents(entity::Registry &registry);
        void invokeHandlers(entity::Registry &registry);
    public:
        bool isEventTypeSupported(const EventType &eventType) override;
        void handleEvents() override;
    };
}


#endif //YAUI_MOUSEEVENTHANDLER_H
