#include "KeyboardEventHandler.h"
#include "component/Components.h"
#include "Director.h"

bool yaui::KeyboardEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return eventType == EventType::SDL_KEYDOWN or eventType == EventType::SDL_KEYUP;
}

void yaui::KeyboardEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto &keyboardEventState = registry.ctx_or_set<component::KeyboardEventState>();

    for(const auto &event: mEventQueue) {
        switch(event.type) {
            case EventType::SDL_KEYDOWN:
                keyboardEventState.keyDown[event.key.keysym.sym] = event;
                for(auto entity: keyboardEventState.listeners) {
                    IEventHandler::invokeEventListeners(registry.get<component::KeyboardEventListener>(entity).onKeyDown, registry, entity, event);
                }
                break;

            case EventType::SDL_KEYUP:
                keyboardEventState.keyUp[event.key.keysym.sym] = event;
                keyboardEventState.keyDown.erase(event.key.keysym.sym);
                for(auto entity: keyboardEventState.listeners) {
                    IEventHandler::invokeEventListeners(registry.get<component::KeyboardEventListener>(entity).onKeyUp, registry, entity, event);
                }
                break;
        }
    }

    mEventQueue.clear();
}
