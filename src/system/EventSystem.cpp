#include "EventSystem.h"
#include "LoggerConstants.h"
#include "MouseEventHandler.h"
#include "TextInputEventHandler.h"
#include "WindowEventHandler.h"

yaui::system::EventSystem::EventSystem(yaui::uint32 priorityRank) {
    ISystem::priorityRank = priorityRank;
    mEventHandlers.emplace_back(new TextInputEventHandler());
    mEventHandlers.emplace_back(new MouseEventHandler());
    mEventHandlers.emplace_back(new WindowEventHandler());
    spdlog::info("{} {}", Logger::kConstructed, EventSystem::getClassName());
}

yaui::system::EventSystem::~EventSystem() {
    for(auto pEventHandlers: mEventHandlers) {
        delete pEventHandlers;
    }
    mEventHandlers.clear();
    spdlog::info("{} {}", Logger::kDestructed, EventSystem::getClassName());
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
    return YAUI_TO_STRING(yaui::system::EventSystem);
}
