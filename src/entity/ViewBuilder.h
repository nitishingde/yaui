#ifndef YAUI_ENTITY_VIEWBUILDER_H
#define YAUI_ENTITY_VIEWBUILDER_H


#include "component/Components.h"

namespace yaui::entity {
    class ViewBuilder {
    private:
        Entity mEntity;
        Registry *mpRegistry = nullptr;

    private:
        explicit ViewBuilder(Entity entity, Registry *pRegistry) noexcept;
    public:
        static ViewBuilder initiateBaseView(Registry &registry);
        ViewBuilder& buildActionItemsComponent(ArrayList<Action> &&actions = {});
        ViewBuilder& buildTextureTransformationComponent(ArrayList<TextureTransformation> &&behaviours = {});
        ViewBuilder& buildBoxModelComponent(const Rect &border = {0, 0, 0, 0}, const Colour &borderColour = {0, 0, 0,255}, const Rect &padding = {0, 0, 0, 0});
        ViewBuilder& buildCaretComponent(const Colour &colour = {128, 128, 128, 128}, const ViewPort &rect = {0, 0, 5, 32});
        ViewBuilder& buildFocusEventListenerComponent(bool isEnabled = false, bool isInFocus = false);
        ViewBuilder& buildFocusEventListenerComponent(EventHandlerFunctionPointer pOnFocus = nullptr, EventHandlerFunctionPointer pOnUnFocus = nullptr);
        ViewBuilder& buildMouseEventListenerComponent(
            EventHandlerFunctionPointer pOnButtonDown = nullptr,
            EventHandlerFunctionPointer pOnButtonUp = nullptr,
            EventHandlerFunctionPointer pOnClick = nullptr,
            EventHandlerFunctionPointer pOnHoverEnter = nullptr,
            EventHandlerFunctionPointer pOnHoverLeave = nullptr,
            EventHandlerFunctionPointer pOnScroll = nullptr
        );
        ViewBuilder& buildTextComponent(String textString, const String& font = "OpenSans-Regular.ttf", const int32 &fontSize = 24, const Colour &fontColour = {0, 0, 0, 255});
        ViewBuilder& buildTextInputEventListener(EventHandlerFunctionPointer pOnCharacterEntered = nullptr, EventHandlerFunctionPointer pOnSpecialKeyPressed = nullptr);
        ViewBuilder& buildTexture2DComponent(const Colour &backgroundColour = {255, 255, 255, 255}, uint32 zIndex = 0);
        ViewBuilder& buildTransformComponent(const ViewPort &viewPort = {0, 0, 0, 0}, const FVec2 &scale = {1, 1});
        Entity buildView();
    };
}


#endif //YAUI_ENTITY_VIEWBUILDER_H
