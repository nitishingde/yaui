#include "FocusEventHandler.h"
#include "component/Components.h"
#include "Director.h"

bool yaui::FocusEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return false;
}

void yaui::FocusEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto view = registry.view<component::FocusEventListener>();
    auto &focusEventState = registry.ctx_or_set<component::FocusEventState>();
    auto &mouseEventState = registry.ctx_or_set<component::MouseEventState>();

    if(mouseEventState.eventTriggerForTargetEntity.type == EventType::SDL_MOUSEBUTTONDOWN) {
        for(auto entity: view) {
            auto &focusEventHandler = view.get(entity);
            if(entity == mouseEventState.targetEntity) {
                if(focusEventHandler.isInFocus()) continue;
                focusEventHandler.isFocused = true;
                IEventHandler::invokeEventListeners(focusEventHandler.onFocusListeners, registry, entity, mouseEventState.eventTriggerForTargetEntity);
            } else {
                focusEventHandler.isFocused = false;
                IEventHandler::invokeEventListeners(focusEventHandler.onUnFocusListeners, registry, entity, mouseEventState.eventTriggerForTargetEntity);
            }
        }
    }
}
