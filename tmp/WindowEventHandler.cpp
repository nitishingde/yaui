#include "WindowEventHandler.h"
#include "Director.h"

bool yaui::WindowEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return eventType == SDL_WINDOWEVENT;
}

void yaui::WindowEventHandler::handleEvents() {
    for(const auto &event: mEventQueue) {
        if(event.window.event == SDL_WindowEventID::SDL_WINDOWEVENT_CLOSE) {
            Director::getInstance()->quit();
            break;
        }
    }

    mEventQueue.clear();
}
