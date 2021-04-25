#include "TextInputEventHandler.h"
#include "component/Components.h"
#include "Director.h"

bool yaui::TextInputEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return eventType == EventType::SDL_TEXTINPUT;
}

void yaui::TextInputEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto &textInputEventState = registry.ctx_or_set<component::TextInputEventState>();
    auto view = registry.view<component::TextInputEventListener>();

    if(const auto &listeners = textInputEventState.listeners; !listeners.empty()) {
        for(const auto &event: mEventQueue) {
            textInputEventState.textEntered = event.text.text;
            for(const auto entity: listeners) {
                if(auto pTextInputEventListener = registry.try_get<component::TextInputEventListener>(entity); pTextInputEventListener != nullptr) {
                    IEventHandler::invokeEventListeners(pTextInputEventListener->onCharacterEnteredListeners, registry, entity, event);
                }
            }
        }
    }

    mEventQueue.clear();
}
