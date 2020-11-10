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
    auto view = registry.view<component::TextInputEventListener>();
    if(auto *pListeners = EventDispatcher::getInstance()->getEventListeners(YAUI_TO_STRING(TextInputEventListener)); pListeners) {
        for(auto &event: mEventQueue) {
            switch(event.type) {
                case EventType::SDL_TEXTINPUT:
                    for(auto &listener: *pListeners) {
                        if(listener.pRegistry != &registry) continue;
                        if(auto pTextInputEventListener = registry.try_get<component::TextInputEventListener>(
                                listener.entity);
                            pTextInputEventListener != nullptr) {
                            IEventHandler::invokeEventListeners(
                                pTextInputEventListener->onCharacterEnteredListeners,
                                registry,
                                listener.entity,
                                event
                            );
                        }
                    }
                    break;

                case EventType::SDL_KEYDOWN:
                    if(event.key.keysym.sym != SDL_KeyCode::SDLK_BACKSPACE) break;
                    for(auto &listener: *pListeners) {
                        if(listener.pRegistry != &registry) continue;
                        if(auto pTextInputEventListener = registry.try_get<component::TextInputEventListener>(
                                listener.entity);
                            pTextInputEventListener != nullptr) {
                            IEventHandler::invokeEventListeners(
                                pTextInputEventListener->onSpecialKeyPressedListeners,
                                registry,
                                listener.entity,
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
