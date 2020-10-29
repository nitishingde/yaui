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

yaui::entity::Entity yaui::entity::ViewFactory::produceTextField(
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
    const int32 &y,
    const Size &dimension
) {
    return ViewBuilder::initiateBaseView(registry)
        .buildActionItemsComponent({Action(
            "Caret Blink",
            1.0f,
            [](entity::Registry &registry, const entity::Entity &entity, float delay, uint64 counter) {
                auto [caret, textureTransformationJobs] = registry.get<component::Caret, component::TextureTransformationJobs>(entity);
                caret.isVisible = !caret.isVisible;
                textureTransformationJobs.trigger();
                return true;
            }
        )})
        .buildBoxModelComponentComponent(border, borderColour, padding)
        .buildCaretComponent()
        .buildTextComponent(textString, fontName, fontSize, foregroundColour)
        .buildTextureTransformationComponent({
            TextureTransformationFactory::produceAddBackgroundColourTextureTransformation(),
            TextureTransformationFactory::produceAddTextFieldTextureTransformation(),
            TextureTransformationFactory::produceAddBorderTextureTransformation()
        })
        .buildTextInputEventListener(
            true,
            [](entity::Registry &registry, const entity::Entity &entity, const Event &event) {
                auto [text, textureTransformationJobs] = registry.get<component::Text, component::TextureTransformationJobs>(entity);
                text.value += event.text.text;
                textureTransformationJobs.trigger();
            },
            [](entity::Registry &registry, const entity::Entity &entity, const Event &event) {
                if(event.key.keysym.sym == SDL_KeyCode::SDLK_BACKSPACE) {
                    auto [text, textureTransformationJobs] = registry.get<component::Text, component::TextureTransformationJobs>(entity);
                    if(text.value.size()) {
                        text.value.resize(text.value.size()-1);
                        textureTransformationJobs.trigger();
                    }
                }
            }
        )
        .buildTexture2DComponent(backgroundColour, 0)
        .buildTransformComponent({x, y, int32(dimension.width) ,int32(dimension.height)})
        .buildView();
}