#include "IEventHandler.h"

static yaui::IEventHandler *instance = nullptr;

void yaui::IEventHandler::enqueueEvent(const yaui::Event &event) {
    mEventQueue.emplace_back(event);
}

void yaui::IEventHandler::handleEventListeners(
    ArrayList<EventHandlerFunctionPointer> &eventListeners,
    entity::Registry &registry,
    const entity::Entity &entity,
    const Event &event
) {
    auto finalSize = eventListeners.size();
    for(int32 index = 0, freeSlot = -1; index < eventListeners.size(); ++index) {
        if(!eventListeners[index](registry, entity, event)) {
            finalSize--;
            if(freeSlot == -1) freeSlot = index;
        } else if(freeSlot != -1) {
            eventListeners[freeSlot] = eventListeners[index];
            freeSlot++;
        }
    }
    eventListeners.resize(finalSize);
}
