#include "MouseEventListener.h"

void
yaui::component::MouseEventListener::onButtonDown(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event)const {
    if(pOnButtonDownHandle) {
        pOnButtonDownHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onButtonUp(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnButtonUpHandle) {
        pOnButtonUpHandle(registry, entity, event);
    }
}

void yaui::component::MouseEventListener::onClick(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnClickHandle) {
        pOnClickHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onHoverEnter(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnHoverEnterHandle) {
        pOnHoverEnterHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onHoverLeave(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnHoverLeaveHandle) {
        pOnHoverLeaveHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onScroll(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnScrollHandle) {
        pOnScrollHandle(registry, entity, event);
    }
}

