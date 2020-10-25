#include "EventSystem.h"
#include <spdlog/spdlog.h>
#include "yaui.h"

yaui::system::EventSystem::EventSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    mEventHandlers.emplace_back(new MouseEventHandler());
    mEventHandlers.emplace_back(new WindowEventHandler());
}

yaui::system::EventSystem::~EventSystem() {
    spdlog::info("DELETED| EventSystem");
    for(auto pEventHandlers: mEventHandlers) {
        delete pEventHandlers;
    }
    mEventHandlers.clear();
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

yaui::String yaui::system::EventSystem::getClassName() const {
    return "EventSystem";
}
