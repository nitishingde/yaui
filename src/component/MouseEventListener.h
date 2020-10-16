#ifndef YAUI_COMPONENT_MOUSEEVENTLISTENER_H
#define YAUI_COMPONENT_MOUSEEVENTLISTENER_H


#include "Types.h"

namespace yaui::component {
    struct MouseEventListener {
        EventHandlerFunctionPointer pOnButtonDownHandle = nullptr;
        EventHandlerFunctionPointer pOnButtonUpHandle = nullptr;
        EventHandlerFunctionPointer pOnClickHandle = nullptr;
        EventHandlerFunctionPointer pOnHoverEnterHandle = nullptr;
        EventHandlerFunctionPointer pOnHoverLeaveHandle = nullptr;
        EventHandlerFunctionPointer pOnScrollHandle = nullptr;

        void onButtonDown(entity::Registry &registry, const entity::Entity &entity, const Event &event) const;
        void onButtonUp(entity::Registry &registry, const entity::Entity &entity, const Event &event) const;
        void onClick(entity::Registry &registry, const entity::Entity &entity, const Event &event) const;
        void onHoverEnter(entity::Registry &registry, const entity::Entity &entity, const Event &event) const;
        void onHoverLeave(entity::Registry &registry, const entity::Entity &entity, const Event &event) const;
        void onScroll(entity::Registry &registry, const entity::Entity &entity, const Event &event) const;
    };
}


#endif //YAUI_COMPONENT_MOUSEEVENTLISTENER_H
