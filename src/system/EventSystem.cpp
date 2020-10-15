#include "EventSystem.h"
#include "yaui.h"

yaui::system::EventSystem::EventSystem(yaui::uint32 priorityRank) {
    ISystem::mPriorityRank = priorityRank;
    mEventHandlers.emplace_back(new MouseEventHandler());
    mEventHandlers.emplace_back(new WindowEventHandler());
}

void yaui::system::EventSystem::pollEvents() {
    Event event;
    while(SDL_PollEvent(&event)) {
        for(auto pEventHandler: mEventHandlers) {
            if(pEventHandler->isEventTypeSupported(EventType(event.type))) {
                pEventHandler->enqueueEvent(event);
            }
        }
    }
}

void yaui::system::EventSystem::executeJob() {
    pollEvents();
    for(auto pEventHandler: mEventHandlers) {
        pEventHandler->handleEvents();
    }
}
