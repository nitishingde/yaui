#include "FocusEventHandler.h"
#include "component/Components.h"
#include "Director.h"
#include "Utility.h"

bool yaui::FocusEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return eventType == EventType::SDL_MOUSEBUTTONDOWN or eventType == EventType::SDL_KEYDOWN;
}

void yaui::FocusEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto view = registry.view<component::FocusEventListener, component::Transform>();

    for(const auto &event: mEventQueue) {
        switch(event.type) {
            case EventType::SDL_MOUSEBUTTONDOWN:
                for(auto &entity: view) {
                    if(auto &focusEventListener = view.get<component::FocusEventListener>(entity); focusEventListener.isInFocus()) {
                        if(!isColliding(registry.get<component::Transform>(entity).viewPort, Vec2{event.button.x, event.button.y})) {
                            focusEventListener.isFocused = false;
                            IEventHandler::invokeEventListeners(focusEventListener.onUnFocusListeners, registry, entity, event);
                        }
                    }
                }
                break;

            case EventType::SDL_KEYDOWN:
                if(event.key.keysym.sym != SDL_KeyCode::SDLK_TAB) continue;
                for(auto &entity: view) {
                    if(auto &focusEventListener = view.get<component::FocusEventListener>(entity); focusEventListener.isInFocus()) {
                        focusEventListener.isFocused = false;
                        IEventHandler::invokeEventListeners(focusEventListener.onUnFocusListeners, registry, entity, event);
                    }
                }
                break;
        }
    }
    mEventQueue.clear();
}
