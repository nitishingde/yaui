#ifndef YAUI_COMPONENT_COMPONENTS_H
#define YAUI_COMPONENT_COMPONENTS_H

#include "Action.h"
#include "Behaviour.h"
#include "TextureTransformation.h"
#include "Types.h"

namespace yaui::component {
    struct ActionItems {
        ArrayList<Action> actions;
    };

    struct BehaviourTraits {
        ArrayList<Behaviour> behaviours;
    };

    struct Caret {
        Colour colour {128, 128, 128, 128};
        bool isVisible = true;
        ViewPort rect {0, 0, 5, 32};
    };

    struct BoxModel {
        Rect border {0, 0, 0, 0};
        Colour borderColour {0, 0, 0, 0};
        Rect padding {0, 0, 0, 0};
    };

    struct MouseEventListener {
        ArrayList<EventHandlerFunctionPointer> onButtonDownListeners;
        ArrayList<EventHandlerFunctionPointer> onButtonUpListeners;
        ArrayList<EventHandlerFunctionPointer> onClickListeners;
        ArrayList<EventHandlerFunctionPointer> onHoverEnterListeners;
        ArrayList<EventHandlerFunctionPointer> onHoverLeaveListeners;
        ArrayList<EventHandlerFunctionPointer> onScrollListeners;
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

    struct TextInputEventListener {
        bool isSelected = false;
        ArrayList<EventHandlerFunctionPointer> onCharacterEnteredListeners;
        ArrayList<EventHandlerFunctionPointer> onSpecialKeyPressedListeners;
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

    struct TextureTransformationJobs {
        bool isTriggered = true;
        ArrayList<TextureTransformation> textureTransformations;
        void trigger();
    };

    struct Transform {
        ViewPort viewPort {0, 0, 0, 0};
        FVec2 scale {1.f, 1.f};
    };
}

#endif //YAUI_COMPONENT_COMPONENTS_H
