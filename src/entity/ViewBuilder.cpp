#include "ViewBuilder.h"

yaui::entity::ViewBuilder::ViewBuilder(Entity entity, Registry *pRegistry) noexcept
    : mEntity(entity)
    , mpRegistry(pRegistry) {

}

yaui::entity::ViewBuilder yaui::entity::ViewBuilder::initiateBaseView(yaui::entity::Registry &registry) {
    return ViewBuilder(registry.create(), &registry);
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildActionItemsComponent(ArrayList<Action> &&actions) {
    auto &actionItems = mpRegistry->emplace_or_replace<component::ActionItems>(mEntity);
    actionItems.actions = std::move(actions);

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildTextureTransformationComponent(ArrayList<TextureTransformation> &&behaviours) {
    auto &textureTransformationJobs = mpRegistry->emplace_or_replace<component::TextureTransformationJobs>(mEntity);
    textureTransformationJobs.textureTransformations = std::move(behaviours);
    textureTransformationJobs.trigger();

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildBoxModelComponentComponent(
    const yaui::Rect &border,
    const yaui::Colour &borderColour,
    const yaui::Rect &padding
) {
    auto &boxModel = mpRegistry->emplace_or_replace<component::BoxModel>(mEntity);
    boxModel.border = border;
    boxModel.borderColour = borderColour;
    boxModel.padding = padding;

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildMouseEventListenerComponent() {
    mpRegistry->emplace_or_replace<component::MouseEventListener>(mEntity);

    return *this;
}

yaui::entity::ViewBuilder& yaui::entity::ViewBuilder::buildTextComponent(
    yaui::String textString,
    yaui::String font,
    const yaui::int32 &fontSize,
    const yaui::Colour &fontColour
) {
    auto &text = mpRegistry->emplace_or_replace<component::Text>(mEntity);
    text.value = textString;
    text.pFont = TTF_OpenFont(("resources/open-sans/"+font).c_str(), fontSize);
    text.colour = fontColour;

    return *this;
}

yaui::entity::ViewBuilder&
yaui::entity::ViewBuilder::buildTexture2DComponent(const yaui::Colour &backgroundColour, yaui::uint32 zIndex) {
    auto &texture2D = mpRegistry->emplace_or_replace<component::Texture2D>(mEntity);
    texture2D.backgroundColour = backgroundColour;
    texture2D.zIndex = zIndex;

    return *this;
}

yaui::entity::ViewBuilder&
yaui::entity::ViewBuilder::buildTransformComponent(const yaui::ViewPort &viewPort, const yaui::FVec2 &scale) {
    auto &transform = mpRegistry->emplace_or_replace<component::Transform>(mEntity);
    transform.scale = scale;
    transform.viewPort = viewPort;

    return *this;
}

yaui::entity::Entity yaui::entity::ViewBuilder::buildView() {
    return mEntity;
}
