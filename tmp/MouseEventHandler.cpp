#include "MouseEventHandler.h"
#include "component/Components.h"
#include "Director.h"
#include "Utility.h"

yaui::entity::Entity yaui::MouseEventHandler::getTargetEntity(const yaui::Vec2 &position, yaui::entity::Registry &registry, yaui::entity::Entity previousTargetedEntity) {
    if(previousTargetedEntity != entity::null) {
        if(auto transform = registry.get<component::Transform>(previousTargetedEntity); isColliding(transform.viewPort, position)) {
            return previousTargetedEntity;
        }
    }

    auto view = registry.view<component::Transform>();
    for(const auto entity: view) {
        if(auto &transform = view.get(entity); isColliding(transform.viewPort, position)) {
            return entity;
        }
    }

    return entity::null;
}

void yaui::MouseEventHandler::pollEvents(yaui::entity::Registry &registry) {
    auto &mouseEventState = registry.ctx_or_set<component::MouseEventState>();
    mouseEventState.reset();

    entity::Entity targetEntity = mouseEventState.currentTargetEntity = getTargetEntity(mouseEventState.getCurrentMousePosition(), registry, entity::null);;
    for(const auto &event: mEventQueue) {
        switch(event.type) {
            case EventType::SDL_MOUSEBUTTONDOWN:
            case EventType::SDL_MOUSEBUTTONUP:
                targetEntity = getTargetEntity({event.button.x, event.button.y}, registry, targetEntity);
                break;

            case EventType::SDL_MOUSEMOTION:
                targetEntity = getTargetEntity({event.motion.x, event.motion.y}, registry, targetEntity);
                break;

            case EventType::SDL_MOUSEWHEEL:
                targetEntity = mouseEventState.currentTargetEntity;
                break;
        }
        mouseEventState.setButtonEventDetails(event, targetEntity);
    }
}

void yaui::MouseEventHandler::invokeHandlers(yaui::entity::Registry &registry) {
    auto &mouseEventState = registry.ctx_or_set<component::MouseEventState>();
    // Wheel, hover event handling
    if(mouseEventState.currentTargetEntity == entity::null);
    else if(auto pMouseEventListener = registry.try_get<component::MouseEventListener>(mouseEventState.currentTargetEntity); pMouseEventListener) {
        if(mouseEventState.pScrollTargetedEvent != nullptr) {
            IEventHandler::invokeEventListeners(pMouseEventListener->onScrollListeners, registry, mouseEventState.currentTargetEntity, mouseEventState.pScrollTargetedEvent->event);
        }
        if(mouseEventState.previousTargetEntity != mouseEventState.currentTargetEntity) {
            IEventHandler::invokeEventListeners(pMouseEventListener->onHoverEnterListeners, registry, mouseEventState.currentTargetEntity, Event{});//FIXME: Event {}
        }
    }

    if(mouseEventState.previousTargetEntity != entity::null and mouseEventState.previousTargetEntity != mouseEventState.currentTargetEntity) {
        if(auto pPreviousMouseEventListener = registry.try_get<component::MouseEventListener>(mouseEventState.previousTargetEntity); pPreviousMouseEventListener) {
            IEventHandler::invokeEventListeners(pPreviousMouseEventListener->onHoverLeaveListeners, registry, mouseEventState.previousTargetEntity, Event{});//FIXME: Event {}
        }
    }

    // Button up/click event handling
    for(auto type: {component::MouseEventState::ButtonEventType::LEFT_UP, component::MouseEventState::ButtonEventType::MIDDLE_UP, component::MouseEventState::ButtonEventType::RIGHT_UP}) {
        if(const auto &pButtonEventData = mouseEventState.getButtonTargetedEvent(type); pButtonEventData != nullptr and pButtonEventData->targetEntity != entity::null) {
            if(auto pMouseEventListener = registry.try_get<component::MouseEventListener>(pButtonEventData->targetEntity); pMouseEventListener) {
                IEventHandler::invokeEventListeners(pMouseEventListener->onButtonUpListeners, registry, pButtonEventData->targetEntity, pButtonEventData->event);
                IEventHandler::invokeEventListeners(pMouseEventListener->onClickListeners, registry, pButtonEventData->targetEntity, pButtonEventData->event);
            }
        }
    }

    // Button down event handling
    for(auto type: {component::MouseEventState::ButtonEventType::LEFT_DOWN, component::MouseEventState::ButtonEventType::MIDDLE_DOWN, component::MouseEventState::ButtonEventType::RIGHT_DOWN}) {
        if(const auto &pButtonEventData = mouseEventState.getButtonTargetedEvent(type); pButtonEventData != nullptr and pButtonEventData->targetEntity != entity::null) {
            if(auto pMouseEventListener = registry.try_get<component::MouseEventListener>(pButtonEventData->targetEntity); pMouseEventListener) {
                IEventHandler::invokeEventListeners(pMouseEventListener->onButtonDownListeners, registry, pButtonEventData->targetEntity, pButtonEventData->event);
            }
        }
    }
}

bool yaui::MouseEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return std::any_of(mValidEventTypes.begin(), mValidEventTypes.end(), [&eventType](uint32 validEventType) {
        return validEventType == eventType;
    });
}

void yaui::MouseEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    pollEvents(registry);
    invokeHandlers(registry);
    mEventQueue.clear();
}
