#include "TextInputEventHandler.h"
#include "component/Components.h"
#include "Director.h"

bool yaui::TextInputEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return eventType == EventType::SDL_TEXTINPUT or eventType == EventType::SDL_KEYDOWN;
}

void yaui::TextInputEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto view = registry.view<component::TextInputEventListener>();
    for(auto &event: mEventQueue) {
        switch(event.type) {
            case EventType::SDL_TEXTINPUT:
                for(auto &entity: view) {
                    auto &textInputEventListeners = view.get(entity);
                    if(!textInputEventListeners.isSelected) continue;
                    IEventHandler::invokeEventListeners(textInputEventListeners.onCharacterEnteredListeners, registry, entity, event);
                }
                break;

            case EventType::SDL_KEYDOWN:
                if(event.key.keysym.sym != SDL_KeyCode::SDLK_BACKSPACE) break;
                for(auto &entity: view) {
                    auto &textInputEventListeners = view.get(entity);
                    if(!textInputEventListeners.isSelected) continue;
                    IEventHandler::invokeEventListeners(textInputEventListeners.onSpecialKeyPressedListeners, registry, entity, event);
                }
                break;
        }
    }
    mEventQueue.clear();
}
