#include "TextureTransformationFactory.h"
#include "yaui.h"

yaui::TextureTransformation yaui::TextureTransformationFactory::produceAddBackgroundColourTextureTransformation() {
    return yaui::TextureTransformation(
        "Background",
        [](Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta) {
            auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;

            // apply background colour
            SDL_SetRenderDrawColor(&renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
            SDL_RenderClear(&renderer);
        }
    );
}

yaui::TextureTransformation yaui::TextureTransformationFactory::produceAddBorderTextureTransformation() {
    return yaui::TextureTransformation(
        "Border",
        [](Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta) {
            auto [boxModel, transform] = registry.get<component::BoxModel, component::Transform>(entity);
            auto &border = boxModel.border;
            auto &borderColour = boxModel.borderColour;
            SDL_SetRenderDrawColor(&renderer, borderColour.r, borderColour.g, borderColour.b, borderColour.a);
            for(uint32 i=0, limit = std::max({border.bottom, border.left, border.right, border.top}); i < limit; ++i) {
                if(i<border.bottom) SDL_RenderDrawLine(&renderer, 0, transform.viewPort.h - i, transform.viewPort.w, transform.viewPort.h - i);
                if(i<border.left) SDL_RenderDrawLine(&renderer, i, 0, i, transform.viewPort.h);
                if(i<border.right) SDL_RenderDrawLine(&renderer, transform.viewPort.w - i, 0, transform.viewPort.w - i, transform.viewPort.h);
                if(i<border.top) SDL_RenderDrawLine(&renderer, 0, i, transform.viewPort.w, i);
            }
        }
    );
}

yaui::TextureTransformation yaui::TextureTransformationFactory::produceAddLabelTextureTransformation() {
    return TextureTransformation(
        "Label",
        [](Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta) {
            // get all the required components
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

yaui::TextureTransformation yaui::TextureTransformationFactory::produceAddTextFieldTextureTransformation() {
    return yaui::TextureTransformation(
        "TextField",
        [](Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta) {
            // get all the required components
            auto [boxModel, caret, text, transform] = registry.get<
                component::BoxModel,
                component::Caret,
                component::Text,
                component::Transform
            >(entity);
            if(text.value.empty()) return;
            auto &padding = boxModel.padding;
            auto &border = boxModel.border;

            // create a texture with the text
            auto pSurface = TTF_RenderText_Blended(text.pFont, text.value.c_str(), text.colour);
            auto pLabelTexture = SDL_CreateTextureFromSurface(&renderer, pSurface);
            SDL_FreeSurface(pSurface);

            // calculate width, height and add padding
            auto &viewPort = transform.viewPort;
            int textWidth, textHeight;
            SDL_QueryTexture(pLabelTexture, nullptr, nullptr, &textWidth, &textHeight);
            auto leftSpace = int32(padding.left+border.left);
            auto rightSpace = int32(padding.right+border.right);
            auto topSpace = int32(padding.top+border.top);
            auto bottomSpace = int32(padding.bottom+border.bottom);

            ViewPort contentRect {
                leftSpace,
                std::max(topSpace, (viewPort.h-textHeight)/2),
                std::min(textWidth, viewPort.w-leftSpace-rightSpace),
                std::min(textHeight, viewPort.h-topSpace-bottomSpace)
            };

            ViewPort srcRect {
                std::max(0, textWidth-contentRect.w),
                0,
                std::min(textWidth, contentRect.w),
                std::min(textHeight, contentRect.h)
            };

            SDL_RenderCopy(&renderer, pLabelTexture, &srcRect, &contentRect);
            SDL_DestroyTexture(pLabelTexture);

            if(caret.isVisible) {
                caret.rect.x = contentRect.x+srcRect.w;
                caret.rect.y = contentRect.y;
                caret.rect.h = contentRect.h;
                SDL_SetRenderDrawColor(&renderer, caret.colour.r, caret.colour.g, caret.colour.b, caret.colour.a);
                SDL_RenderFillRect(&renderer, &caret.rect);
            }
        }
    );
}
