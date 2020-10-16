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
        entity::Registry *mpPreviousTargetRegistry = nullptr;
        entity::Entity mPreviousTargetEntity = entity::null;

    private:
        [[nodiscard]] bool isWithinBoundaries(const ViewPort &viewPort, const Vec2 &mousePosition) const;
    public:
        bool isEventTypeSupported(const EventType &eventType) override;
        void handleEvents() override;
    };
}


#endif //YAUI_MOUSEEVENTHANDLER_H
