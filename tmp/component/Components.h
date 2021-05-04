#ifndef YAUI_COMPONENT_COMPONENTS_H
#define YAUI_COMPONENT_COMPONENTS_H

#include "Action.h"
#include "Behaviour.h"
#include "TextureTransformation.h"
#include "Types.h"

namespace yaui::component {
    struct ActionItems {
        ArrayList<Action> actions;
    } __attribute__((aligned(32)));

    struct BehaviourTraits {
        ArrayList<Behaviour> behaviours;
    } __attribute__((aligned(32)));

    struct Caret {
        Colour colour {128, 128, 128, 128};
        bool isVisible = false;
        ViewPort rect {0, 0, 5, 32};
    } __attribute__((aligned(32)));

    struct BoxModel {
        Rect border {0, 0, 0, 0};
        Colour borderColour {0, 0, 0, 0};
        Rect padding {0, 0, 0, 0};
    } __attribute__((aligned(64)));

    struct FocusEventListener {
        bool isEnabled = false;
        bool isFocused = false;
        ArrayList<EventHandlerFunctionPointer> onFocusListeners;
        ArrayList<EventHandlerFunctionPointer> onUnFocusListeners;
        [[nodiscard]] bool isInFocus() const;
    } __attribute__((aligned(64)));

    struct KeyboardEventListener {
        ArrayList<EventHandlerFunctionPointer> onKeyDown;
        ArrayList<EventHandlerFunctionPointer> onKeyUp;
        void registerListener(entity::Registry &registry, const entity::Entity &entity);
        void unregisterListener(entity::Registry &registry, const entity::Entity &entity);
    } __attribute__((aligned(64)));

    struct MouseEventListener {
        ArrayList<EventHandlerFunctionPointer> onButtonDownListeners;
        ArrayList<EventHandlerFunctionPointer> onButtonUpListeners;
        ArrayList<EventHandlerFunctionPointer> onClickListeners;
        ArrayList<EventHandlerFunctionPointer> onHoverEnterListeners;
        ArrayList<EventHandlerFunctionPointer> onHoverLeaveListeners;
        ArrayList<EventHandlerFunctionPointer> onScrollListeners;
    } __attribute__((aligned(128)));

    struct Text {
        Colour colour {0, 0, 0, 255};
        String value;
        Font *pFont = nullptr;
        explicit Text() noexcept;
        Text(Text &&other) noexcept;
        Text& operator=(Text &&other) noexcept;
        ~Text();
    } __attribute__((aligned(64)));

    struct TextInputEventListener: public IEventListener {
        ArrayList<EventHandlerFunctionPointer> onCharacterEnteredListeners;
        [[nodiscard]] String getClassName() const override;
        void registerListener(entity::Registry &registry, const entity::Entity &entity);
        void unregisterListener(entity::Registry &registry, const entity::Entity &entity);
    } __attribute__((aligned(32)));

    struct Texture2D {
        Colour backgroundColour{0, 0, 0, 0};
        uint32 zIndex = 0;
        Texture *pTexture = nullptr;
        explicit Texture2D() noexcept;
        Texture2D(Texture2D &&other) noexcept;
        Texture2D& operator=(Texture2D &&other) noexcept;
        ~Texture2D();
    } __attribute__((aligned(16)));

    struct TextureTransformationJobs {
        bool isTriggered = true;
        ArrayList<TextureTransformation> textureTransformations;
        void trigger();
    } __attribute__((aligned(32)));

    struct Transform {
        ViewPort viewPort {0, 0, 0, 0};
        FVec2 scale {1.f, 1.f};
    } __attribute__((aligned(32)));

    // Context variables
    struct FocusEventState {
        Event eventTriggerForTargetEntity = Event{};
        entity::Entity targetEntity = entity::null;
    } __attribute__((aligned(64)));

    struct KeyboardEventState {
        HashMap<int32, Event> keyUp;
        HashMap<int32, Event> keyDown;
        Set<entity::Entity> listeners;
    } __attribute__((aligned(128)));

    struct MouseEventState {
    private:
        ArrayList<TargetedEvent> mMotionTrackingQueue;
        const int kMotionTrackingLimit = 4;
        ArrayList<std::unique_ptr<TargetedEvent>> mButtonEvents {6};
    public:
        std::unique_ptr<TargetedEvent> pScrollTargetedEvent;
        enum ButtonEventType {
            LEFT_DOWN = 0,
            LEFT_UP = 1,
            MIDDLE_DOWN = 2,
            MIDDLE_UP = 3,
            RIGHT_DOWN = 4,
            RIGHT_UP = 5,
        };
        entity::Entity currentTargetEntity = entity::null;
        entity::Entity previousTargetEntity = entity::null;

    private:
        void resizeMouseMotionTracking();
    public:
        void reset();
        Vec2 getCurrentMousePosition();
        Vec2 getCurrentGlobalMousePosition();
        [[nodiscard]] const std::unique_ptr<TargetedEvent>& getButtonTargetedEvent(ButtonEventType type) const;
        const ArrayList<TargetedEvent>& getMotionTrackingQueue();
        void setButtonEventDetails(const Event &event, entity::Entity targetEntity);
    } __attribute__((aligned(128)));

    struct TextInputEventState {
        String textEntered;
        Set<entity::Entity> listeners;
    } __attribute__((aligned(128)));
}

#endif //YAUI_COMPONENT_COMPONENTS_H
