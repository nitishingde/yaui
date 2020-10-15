#include "IEventHandler.h"

static yaui::IEventHandler *instance = nullptr;

void yaui::IEventHandler::enqueueEvent(const yaui::Event &event) {
    mEventQueue.emplace_back(event);
}
