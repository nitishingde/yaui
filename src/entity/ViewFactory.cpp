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
    return ViewBuilder::initiateBaseView(registry)
        .buildBoxModelComponentComponent(border, borderColour, padding)
        .buildBehaviourTraitsComponent({
            BehaviourFactory::produceAddBackgroundColourBehaviour(),
            BehaviourFactory::produceAddTextBehaviour(),
            BehaviourFactory::produceAddBorderBehaviour()
        })
        .buildTextComponent(textString, fontName, fontSize, foregroundColour)
        .buildTexture2DComponent(backgroundColour)
        .buildTransformComponent({x, y, 213, 54})
        .buildView();
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
