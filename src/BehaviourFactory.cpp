#include "BehaviourFactory.h"
#include "yaui.h"

yaui::Behaviour yaui::BehaviourFactory::produceAddBackgroundColourBehaviour() {
    return yaui::Behaviour(
        "Background",
        [](entity::Registry &registry, const entity::Entity &entity, float delta) {
            auto &renderer = registry.ctx<RendererWrapper>().getRenderer();
            auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;

            // apply background colour
            SDL_SetRenderDrawColor(&renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
            SDL_RenderClear(&renderer);
        }
    );
}

yaui::Behaviour yaui::BehaviourFactory::produceAddBorderBehaviour() {
    return yaui::Behaviour(
        "Border",
        [](entity::Registry &registry, const entity::Entity &entity, float delta) {
            auto &renderer = registry.ctx<RendererWrapper>().getRenderer();
            auto [boxModel, transform, texture2D] = registry.get<component::BoxModel, component::Transform, component::Texture2D>(entity);
            auto &border = boxModel.border;
            auto &borderColour = boxModel.borderColour;
            SDL_SetRenderTarget(&renderer, texture2D.pTexture);
            SDL_SetRenderDrawColor(&renderer, borderColour.r, borderColour.g, borderColour.b, borderColour.a);
            for(uint32 i=0, limit = std::max({border.bottom, border.left, border.right, border.top}); i < limit; ++i) {
                if(i<border.bottom) SDL_RenderDrawLine(&renderer, 0, transform.viewPort.h - i, transform.viewPort.w, transform.viewPort.h - i);
                if(i<border.left) SDL_RenderDrawLine(&renderer, i, 0, i, transform.viewPort.h);
                if(i<border.right) SDL_RenderDrawLine(&renderer, transform.viewPort.w - i, 0, transform.viewPort.w - i, transform.viewPort.h);
                if(i<border.top) SDL_RenderDrawLine(&renderer, 0, i, transform.viewPort.w, i);
            }
            SDL_SetRenderTarget(&renderer, nullptr);
        }
    );
}

yaui::Behaviour yaui::BehaviourFactory::produceAddTextBehaviour() {
    return Behaviour(
        "Label",
        [](entity::Registry &registry, const entity::Entity &entity, float delta) {
            // get the renderer and all required components
            auto &renderer = registry.ctx<RendererWrapper>().getRenderer();
            auto [boxModel, text] = registry.get<component::BoxModel, component::Text>(entity);
            auto &padding = boxModel.padding;
            auto &border = boxModel.border;

            // create a texture with the text
            auto pSurface = TTF_RenderText_Blended(text.pFont, text.value.c_str(), text.colour);
            auto pLabelTexture = SDL_CreateTextureFromSurface(&renderer, pSurface);
            SDL_FreeSurface(pSurface);

            // calculate width, height and add padding
            int width, height;
            SDL_QueryTexture(pLabelTexture, nullptr, nullptr, &width, &height);
            SDL_Rect rect {int(padding.left+border.left), int(padding.top+border.top), width, height};
            SDL_RenderCopy(&renderer, pLabelTexture, nullptr, &rect);
            SDL_DestroyTexture(pLabelTexture);
        }
    );
}
