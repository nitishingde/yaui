#include "EventPollingSystem.h"
#include "yaui.h"

yaui::system::EventPollingSystem::EventPollingSystem(yaui::uint32 priorityRank) {
    ISystem::mPriorityRank = priorityRank;
}

void yaui::system::EventPollingSystem::handleMouseEvents(const yaui::Event &event) {
    auto &scene = Director::getInstance()->getScene();
    auto &registry = scene.getRegistry();
    Vec2 mousePosition = {event.motion.x, event.motion.y};
    auto view = registry.view<component::Transform>();
    entity::Entity targetEntity = entity::null;
    for(auto entityIterator=view.rbegin(); entityIterator != view.rend(); entityIterator++) {
        auto transform = view.get(*entityIterator);
        if(mousePosition.x < transform.viewPort.x or transform.viewPort.x+transform.viewPort.w < mousePosition.x) continue;
        if(mousePosition.y < transform.viewPort.y or transform.viewPort.y+transform.viewPort.h < mousePosition.y) continue;
        targetEntity = *entityIterator;
        break;
    }

    // validate entity and check if the entity has a MouseEventListener component
    if(targetEntity == entity::null) return;
    auto pMouseEventListener = registry.try_get<component::MouseEventListener>(targetEntity);
    if(pMouseEventListener == nullptr) return;

    pMouseEventListener->onHover(registry, targetEntity, event);
    switch(event.type) {
        case SDL_EventType::SDL_MOUSEBUTTONDOWN:
            pMouseEventListener->onButtonDown(registry, targetEntity, event);
            break;

        case SDL_EventType::SDL_MOUSEBUTTONUP:
            pMouseEventListener->onButtonUp(registry, targetEntity, event);
            pMouseEventListener->onClick(registry, targetEntity, event);
            break;

        case SDL_EventType::SDL_MOUSEMOTION:
            break;

        case SDL_EventType::SDL_MOUSEWHEEL:
            pMouseEventListener->onScroll(registry, targetEntity, event);
            break;
    }
}

void yaui::system::EventPollingSystem::executeJob() {
    Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EventType::SDL_MOUSEBUTTONDOWN:
            case SDL_EventType::SDL_MOUSEBUTTONUP:
            case SDL_EventType::SDL_MOUSEMOTION:
            case SDL_EventType::SDL_MOUSEWHEEL:
                handleMouseEvents(event);
                break;
            case SDL_EventType::SDL_KEYDOWN:
                if(event.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE) {
                    Director::getInstance()->quit();
                    return;
                }
                break;
        }
    }
}
