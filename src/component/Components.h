#ifndef YAUI_COMPONENT_COMPONENTS_H
#define YAUI_COMPONENT_COMPONENTS_H

#include "Action.h"
#include "Behaviour.h"
#include "Types.h"

namespace yaui::component {
    struct ActionItems {
        ArrayList<Action> actions;
    };

    struct BehaviourTraits {
        bool isTriggered = true;
        ArrayList<Behaviour> behaviours;
        void trigger();
    };

    struct BoxModel {
        Rect border {0, 0, 0, 0};
        Colour borderColour {0, 0, 0, 0};
        Rect padding {0, 0, 0, 0};
    };

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

    struct Text {
        Colour colour {0, 0, 0, 255};
        String value;
        Font *pFont = nullptr;
        explicit Text() = default;
        Text(Text &&other) noexcept;
        Text& operator=(Text &&other) noexcept;
        ~Text();
    };

    struct Texture2D {
        Colour backgroundColour{0, 0, 0, 0};
        uint32 zIndex = 0;
        Texture *pTexture = nullptr;
        explicit Texture2D() = default;
        Texture2D(Texture2D &&other) noexcept;
        Texture2D& operator=(Texture2D &&other) noexcept;
        ~Texture2D();
    };

    struct Transform {
        ViewPort viewPort {0, 0, 0, 0};
        FVec2 scale {1.f, 1.f};
    };
}

#endif //YAUI_COMPONENT_COMPONENTS_H
