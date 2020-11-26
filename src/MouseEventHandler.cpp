#include "MouseEventHandler.h"
#include "yaui.h"

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

    for(auto &event: mEventQueue) {
        Vec2 mousePosition = {event.motion.x, event.motion.y};
        auto view = registry.view<component::Transform>();
        entity::Entity targetEntity = entity::null;
        for(auto entityIterator = view.rbegin(); entityIterator != view.rend(); entityIterator++) {
            auto transform = view.get(*entityIterator);
            if(!isWithinBoundaries(transform.viewPort, mousePosition)) continue;
            targetEntity = *entityIterator;
            break;
        }

        if(mPreviousTargetEntity == targetEntity);
        else if(mpPreviousTargetRegistry == &registry and mPreviousTargetEntity != entity::null) {
            auto pMouseEventListener = registry.try_get<component::MouseEventListener>(mPreviousTargetEntity);
            if(pMouseEventListener) {
                IEventHandler::invokeEventListeners(pMouseEventListener->onHoverLeaveListeners, registry, mPreviousTargetEntity, event);
            }
            mPreviousTargetEntity = entity::null;
        }

        // validate entity and check if the entity has a MouseEventListener component
        if(targetEntity == entity::null) continue;
        auto pMouseEventListener = registry.try_get<component::MouseEventListener>(targetEntity);
        if(pMouseEventListener == nullptr) continue;

        mPreviousTargetEntity = targetEntity;
        IEventHandler::invokeEventListeners(pMouseEventListener->onHoverEnterListeners, registry, targetEntity, event);
        switch(event.type) {
            case SDL_EventType::SDL_MOUSEBUTTONDOWN:
                IEventHandler::invokeEventListeners(pMouseEventListener->onButtonDownListeners, registry, targetEntity, event);
                // FIXME: this should not be here
                if(auto focusEventListener = registry.try_get<component::FocusEventListener>(targetEntity); focusEventListener and focusEventListener->isEnabled and !focusEventListener->isFocused) {
                    focusEventListener->isFocused = true;
                    IEventHandler::invokeEventListeners(focusEventListener->onFocusListeners, registry, targetEntity, event);
                }
                break;

            case SDL_EventType::SDL_MOUSEBUTTONUP:
                IEventHandler::invokeEventListeners(pMouseEventListener->onButtonUpListeners, registry, targetEntity, event);
                IEventHandler::invokeEventListeners(pMouseEventListener->onClickListeners, registry, targetEntity, event);
                break;

            case SDL_EventType::SDL_MOUSEMOTION:
                break;

            case SDL_EventType::SDL_MOUSEWHEEL:
                IEventHandler::invokeEventListeners(pMouseEventListener->onScrollListeners, registry, targetEntity, event);
                break;
        }
    }
    mpPreviousTargetRegistry = &registry;
    mEventQueue.clear();
}
