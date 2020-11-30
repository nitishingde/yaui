#include "ViewBuilder.h"

#include <utility>

yaui::entity::ViewBuilder::ViewBuilder(Entity entity, Registry *pRegistry) noexcept
    : mEntity(entity)
    , mpRegistry(pRegistry) {

}

yaui::entity::ViewBuilder yaui::entity::ViewBuilder::initiateBaseView(yaui::entity::Registry &registry) {
    auto viewBuilder = ViewBuilder(registry.create(), &registry);
    return viewBuilder
        .buildTransformComponent()
        .buildBoxModelComponent()
        .buildTexture2DComponent()
        .buildTextureTransformationComponent();
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildActionItemsComponent(ArrayList<Action> &&actions) {
    auto &actionItems = mpRegistry->get_or_emplace<component::ActionItems>(mEntity);
    actionItems.actions = std::move(actions);

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildTextureTransformationComponent(ArrayList<TextureTransformation> &&behaviours) {
    auto &textureTransformationJobs = mpRegistry->get_or_emplace<component::TextureTransformationJobs>(mEntity);
    textureTransformationJobs.textureTransformations = std::move(behaviours);
    textureTransformationJobs.trigger();

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildBoxModelComponent(
    const yaui::Rect &border,
    const yaui::Colour &borderColour,
    const yaui::Rect &padding
) {
    auto &boxModel = mpRegistry->get_or_emplace<component::BoxModel>(mEntity);
    boxModel.border = border;
    boxModel.borderColour = borderColour;
    boxModel.padding = padding;

    return *this;
}

yaui::entity::ViewBuilder&
yaui::entity::ViewBuilder::buildCaretComponent(const yaui::Colour &colour, const yaui::ViewPort &rect) {
    auto &caret = mpRegistry->get_or_emplace<component::Caret>(mEntity);
    caret.colour = colour;
    caret.rect = rect;

    return *this;
}

yaui::entity::ViewBuilder &yaui::entity::ViewBuilder::buildFocusEventListenerComponent(bool isEnabled, bool isInFocus) {
    auto &focus = mpRegistry->get_or_emplace<component::FocusEventListener>(mEntity);
    focus.isEnabled = isEnabled;
    focus.isFocused = isInFocus;

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::emplaceBackListenersToFocusEventListenerComponent(
    yaui::EventHandlerFunctionPointer pOnFocus,
    yaui::EventHandlerFunctionPointer pOnUnFocus
) {
    auto &focus = mpRegistry->get_or_emplace<component::FocusEventListener>(mEntity);
    if(pOnFocus) focus.onFocusListeners.emplace_back(pOnFocus);
    if(pOnUnFocus) focus.onUnFocusListeners.emplace_back(pOnUnFocus);

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::emplaceBackListenersToMouseEventListenerComponent(
    EventHandlerFunctionPointer pOnButtonDown,
    EventHandlerFunctionPointer pOnButtonUp,
    EventHandlerFunctionPointer pOnClick,
    EventHandlerFunctionPointer pOnHoverEnter,
    EventHandlerFunctionPointer pOnHoverLeave,
    EventHandlerFunctionPointer pOnScroll
) {
    auto &mouseEventListener = mpRegistry->get_or_emplace<component::MouseEventListener>(mEntity);
    if(pOnButtonDown) mouseEventListener.onButtonDownListeners.emplace_back(pOnButtonDown);
    if(pOnButtonUp) mouseEventListener.onButtonUpListeners.emplace_back(pOnButtonUp);
    if(pOnClick) mouseEventListener.onClickListeners.emplace_back(pOnClick);
    if(pOnHoverEnter) mouseEventListener.onHoverEnterListeners.emplace_back(pOnHoverEnter);
    if(pOnHoverLeave) mouseEventListener.onHoverLeaveListeners.emplace_back(pOnHoverLeave);
    if(pOnScroll) mouseEventListener.onScrollListeners.emplace_back(pOnScroll);

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildTextComponent(
    yaui::String textString,
    const yaui::String& font,
    const yaui::int32 &fontSize,
    const yaui::Colour &fontColour
) {
    auto &text = mpRegistry->get_or_emplace<component::Text>(mEntity);
    text.value = std::move(textString);
    text.pFont = TTF_OpenFont(("resources/open-sans/"+font).c_str(), fontSize);
    text.colour = fontColour;

    return *this;
}

yaui::entity::ViewBuilder &yaui::entity::ViewBuilder::emplaceBackListenersToTextInputEventListener(
    EventHandlerFunctionPointer pOnCharacterEntered,
    EventHandlerFunctionPointer pOnSpecialKeyPressed
) {
    auto &textInputEventListener = mpRegistry->get_or_emplace<component::TextInputEventListener>(mEntity);
    if(pOnCharacterEntered) textInputEventListener.onCharacterEnteredListeners.emplace_back(pOnCharacterEntered);
    if(pOnSpecialKeyPressed) textInputEventListener.onSpecialKeyPressedListeners.emplace_back(pOnSpecialKeyPressed);

    return *this;
}

yaui::entity::ViewBuilder&
yaui::entity::ViewBuilder::buildTexture2DComponent(const yaui::Colour &backgroundColour, yaui::uint32 zIndex) {
    auto &texture2D = mpRegistry->get_or_emplace<component::Texture2D>(mEntity);
    texture2D.backgroundColour = backgroundColour;
    texture2D.zIndex = zIndex;

    return *this;
}

yaui::entity::ViewBuilder&
yaui::entity::ViewBuilder::buildTransformComponent(const yaui::ViewPort &viewPort, const yaui::FVec2 &scale) {
    auto &transform = mpRegistry->get_or_emplace<component::Transform>(mEntity);
    transform.scale = scale;
    transform.viewPort = viewPort;

    return *this;
}

yaui::entity::Entity yaui::entity::ViewBuilder::buildView() {
    return mEntity;
}
