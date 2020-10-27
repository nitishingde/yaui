#include "ViewFactory.h"
#include "ViewBuilder.h"
#include "yaui.h"

yaui::entity::Entity yaui::entity::ViewFactory::produceLabel(
    Registry &registry,
    const String &textString,
    const String &fontName,
    const uint32 &fontSize,
    const Colour &foregroundColour,
    const Colour &backgroundColour,
    const Rect &padding,
    const Rect &border,
    const Colour &borderColour,
    const int32 &x,
    const int32 &y
) {
    auto entity = ViewBuilder::initiateBaseView(registry)
        .buildBoxModelComponentComponent(border, borderColour, padding)
        .buildTextureTransformationComponent({
             TextureTransformationFactory::produceAddBackgroundColourTextureTransformation(),
             TextureTransformationFactory::produceAddLabelTextureTransformation(),
             TextureTransformationFactory::produceAddBorderTextureTransformation()
        })
        .buildTextComponent(textString, fontName, fontSize, foregroundColour)
        .buildTexture2DComponent(backgroundColour)
        .buildTransformComponent({x, y, 0, 0})
        .buildView();

    auto &transform = registry.get<component::Transform>(entity);
    auto dimension = getDimensionForText(registry.get<component::Text>(entity), registry.try_get<component::BoxModel>(entity));
    transform.viewPort.w = dimension.width;
    transform.viewPort.h = dimension.height;

    return entity;
}

yaui::entity::Entity yaui::entity::ViewFactory::produceButton(
    Registry &registry,
    const String &textString,
    const String &fontName,
    const uint32 &fontSize,
    const Colour &foregroundColour,
    const Colour &backgroundColour,
    const Rect &padding,
    const Rect &border,
    const Colour &borderColour,
    const int32 &x,
    const int32 &y
) {
    auto entity = produceLabel(registry, textString, fontName, fontSize, foregroundColour, backgroundColour, padding, border, borderColour, x, y);
    registry.emplace<component::MouseEventListener>(entity);
    return entity;
}
