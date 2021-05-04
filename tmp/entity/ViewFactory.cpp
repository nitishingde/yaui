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
        .buildBoxModelComponent(border, borderColour, padding)
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
                auto[caret, focusEventListener, textInputEventListener, textureTransformationJobs] = registry.get<
                    component::Caret,
                    component::FocusEventListener,
                    component::TextInputEventListener,
                    component::TextureTransformationJobs
                >(entity);
                bool oldIsVisible = caret.isVisible;
                if(focusEventListener.isInFocus()) caret.isVisible = !caret.isVisible;
                else caret.isVisible = false;
                if(oldIsVisible != caret.isVisible) textureTransformationJobs.trigger();
                return true;
            }
        )})
        .buildBoxModelComponent(border, borderColour, padding)
        .buildCaretComponent()
        .buildFocusEventListenerComponent(true, false)
        .emplaceBackListenersToFocusEventListenerComponent(
            [](entity::Registry &registry, const entity::Entity &entity, const Event &event) {
                if(auto textInputEventListener = registry.try_get<component::TextInputEventListener>(entity); textInputEventListener) {
                    textInputEventListener->registerListener(registry, entity);
                }
                return true;
            },
            [](entity::Registry &registry, const entity::Entity &entity, const Event &event) {
                if(auto textInputEventListener = registry.try_get<component::TextInputEventListener>(entity); textInputEventListener) {
                    textInputEventListener->unregisterListener(registry, entity);
                }
                return true;
            }
        )
        .buildKeyboardEventListenerComponent(true)
        .emplaceBackListenersToKeyboardEventListenerComponent(
            [](entity::Registry &registry, const entity::Entity &entity, const Event &event) {
                if(event.key.keysym.sym == SDL_KeyCode::SDLK_BACKSPACE) {
                    auto [text, textureTransformationJobs] = registry.get<component::Text, component::TextureTransformationJobs>(entity);
                    if(text.value.size()) {
                        text.value.resize(text.value.size()-1);
                        textureTransformationJobs.trigger();
                    }
                }
                return true;
            },
            nullptr
        )
        .emplaceBackListenersToMouseEventListenerComponent()
        .buildTextComponent(textString, fontName, fontSize, foregroundColour)
        .buildTextureTransformationComponent({
            TextureTransformationFactory::produceAddBackgroundColourTextureTransformation(),
            TextureTransformationFactory::produceAddTextFieldTextureTransformation(),
            TextureTransformationFactory::produceAddBorderTextureTransformation()
        })
        .emplaceBackListenersToTextInputEventListener(
            [](entity::Registry &registry, const entity::Entity &entity, const Event &event) {
                auto [text, textureTransformationJobs] = registry.get<component::Text, component::TextureTransformationJobs>(entity);
                text.value += event.text.text;
                textureTransformationJobs.trigger();
                return true;
            }
        )
        .buildTexture2DComponent(backgroundColour, 0)
        .buildTransformComponent({x, y, int32(dimension.width) ,int32(dimension.height)})
        .buildView();
}
