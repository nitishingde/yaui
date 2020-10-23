#include "ViewFactory.h"
#include "yaui.h"

yaui::entity::Entity yaui::entity::ViewFactory::produceLabel(
    Scene &scene,
    const String &textString,
    const String &fontName,
    const uint32 &fontSize,
    const Colour &foregroundColour,
    const Colour &backgroundColour,
    const Rect &padding,
    const Rect &border,
    const int32 &x,
    const int32 &y
) {
    auto &registry = scene.getRegistry();
    auto entity = registry.create();

    // create components
    auto &behaviourTraits = registry.emplace<component::BehaviourTraits>(entity);
    auto &boxModel = registry.emplace<component::BoxModel>(entity);
    auto &text = registry.emplace<component::Text>(entity);
    auto &texture = registry.emplace<component::Texture2D>(entity);
    auto &transform = registry.emplace<component::Transform>(entity);

    behaviourTraits.trigger();
    behaviourTraits.behaviours.emplace_back(BehaviourFactory::produceAddBackgroundColourBehaviour());
    behaviourTraits.behaviours.emplace_back(BehaviourFactory::produceAddTextBehaviour());
    behaviourTraits.behaviours.emplace_back(BehaviourFactory::produceAddBorderBehaviour());

    boxModel.border = border;
    boxModel.padding = padding;
    boxModel.borderColour = Colour {127, 127, 127, 127};

    text.colour = foregroundColour;
    text.value = textString;
    text.pFont = TTF_OpenFont(("../../../resources/open-sans/"+fontName).c_str(), fontSize);

    int width, height;
    TTF_SizeText(text.pFont, text.value.c_str(), &width, &height);
    transform.viewPort = {
        x,
        y,
        width + int(padding.left + padding.right + border.left + border.right),
        height + int(padding.top + padding.bottom + border.top + border.bottom)
    };

    texture.backgroundColour = backgroundColour;

    return entity;
}

yaui::entity::Entity yaui::entity::ViewFactory::produceButton(
    yaui::Scene &scene,
    const yaui::String &textString,
    const yaui::String &fontName,
    const yaui::uint32 &fontSize,
    const yaui::Colour &foregroundColour,
    const yaui::Colour &backgroundColour,
    const yaui::Rect &padding,
    const yaui::Rect &border,
    const yaui::int32 &x,
    const yaui::int32 &y
) {
    auto &registry = scene.getRegistry();
    auto entity = produceLabel(scene, textString, fontName, fontSize, foregroundColour, backgroundColour, padding, border, x, y);
    registry.emplace<component::MouseEventListener>(entity);
    return entity;
}
