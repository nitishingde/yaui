#include "TextInputEventHandler.h"
#include "component/Components.h"
#include "Director.h"
#include "EventDispatcher.h"

bool yaui::TextInputEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return eventType == EventType::SDL_TEXTINPUT or eventType == EventType::SDL_KEYDOWN;
}

void yaui::TextInputEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto &textInputEventState = registry.ctx_or_set<component::TextInputEventState>();
    auto view = registry.view<component::TextInputEventListener>();
    if(auto &listeners = textInputEventState.listeners; !listeners.empty()) {
        for(auto &event: mEventQueue) {
            switch(event.type) {
                case EventType::SDL_TEXTINPUT:
                    textInputEventState.textEntered = event.text.text;
                    for(const auto entity: listeners) {
                        if(auto pTextInputEventListener = registry.try_get<component::TextInputEventListener>(entity);
                            pTextInputEventListener != nullptr) {
                            IEventHandler::invokeEventListeners(
                                pTextInputEventListener->onCharacterEnteredListeners,
                                registry,
                                entity,
                                event
                            );
                        }
                    }
                    break;

                case EventType::SDL_KEYDOWN:
                    if(event.key.keysym.sym != SDL_KeyCode::SDLK_BACKSPACE) break;
                    for(const auto entity: listeners) {
                        if(auto pTextInputEventListener = registry.try_get<component::TextInputEventListener>(entity);
                            pTextInputEventListener != nullptr) {
                            IEventHandler::invokeEventListeners(
                                pTextInputEventListener->onSpecialKeyPressedListeners,
                                registry,
                                entity,
                                event
                            );
                        }
                    }
                    break;
            }
        }
    }
    mEventQueue.clear();
}
