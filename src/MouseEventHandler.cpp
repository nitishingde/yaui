#include "MouseEventHandler.h"
#include "component/Components.h"
#include "Director.h"

bool yaui::MouseEventHandler::isWithinBoundaries(const yaui::ViewPort &viewPort, const yaui::Vec2 &mousePosition) const {
    if(mousePosition.x < viewPort.x or viewPort.x+viewPort.w < mousePosition.x) return false;
    if(mousePosition.y < viewPort.y or viewPort.y+viewPort.h < mousePosition.y) return false;
    return true;
}

bool yaui::MouseEventHandler::isEventTypeSupported(const yaui::EventType &eventType) {
    return std::any_of(mValidEventTypes.begin(), mValidEventTypes.end(), [&eventType](uint32 validEventType) {
        return validEventType == eventType;
    });
}

void yaui::MouseEventHandler::handleEvents() {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    auto &mouseEventState = registry.ctx_or_set<component::MouseEventState>();
    mouseEventState.previousTargetEntity = mouseEventState.targetEntity;
    mouseEventState.targetEntity = entity::null;
    mouseEventState.eventTriggerForTargetEntity = Event{};

    for(const auto &event: mEventQueue) {
        Vec2 mousePosition = {event.motion.x, event.motion.y};
        auto view = registry.view<component::Transform>();
        auto &targetEntity = mouseEventState.targetEntity = entity::null;
        mouseEventState.eventTriggerForTargetEntity = event;
        for(auto entityIterator = view.rbegin(); entityIterator != view.rend(); entityIterator++) {
            auto transform = view.get(*entityIterator);
            if(!isWithinBoundaries(transform.viewPort, mousePosition)) continue;
            targetEntity = *entityIterator;
            break;
        }

        auto &previousTargetEntity = mouseEventState.previousTargetEntity;
        if(previousTargetEntity != targetEntity and previousTargetEntity != entity::null) {
            if(auto pMouseEventListener = registry.try_get<component::MouseEventListener>(previousTargetEntity); pMouseEventListener) {
                IEventHandler::invokeEventListeners(pMouseEventListener->onHoverLeaveListeners, registry, previousTargetEntity, event);
            }
        }

        // validate entity and check if the entity has a MouseEventListener component
        if(targetEntity == entity::null) continue;
        auto pMouseEventListener = registry.try_get<component::MouseEventListener>(targetEntity);
        if(pMouseEventListener == nullptr) continue;

        IEventHandler::invokeEventListeners(pMouseEventListener->onHoverEnterListeners, registry, targetEntity, event);
        switch(event.type) {
            case SDL_EventType::SDL_MOUSEBUTTONDOWN:
                IEventHandler::invokeEventListeners(pMouseEventListener->onButtonDownListeners, registry, targetEntity, event);
                break;

            case SDL_EventType::SDL_MOUSEBUTTONUP:
                IEventHandler::invokeEventListeners(pMouseEventListener->onButtonUpListeners, registry, targetEntity, event);
                IEventHandler::invokeEventListeners(pMouseEventListener->onClickListeners, registry, targetEntity, event);
                break;
        }
    }
    mEventQueue.clear();
}
