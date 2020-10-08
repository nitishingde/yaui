#include "ViewFactory.h"
#include "yaui.h"
#include <unistd.h>

yaui::entity::Entity yaui::entity::ViewFactory::produceLabel(
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
    auto director = Director::getInstance();
    auto &renderer = director->getRenderer();
    auto &registry = director->getRegistry();
    auto entity = registry.create();

    // create components
    auto &boxModel = registry.emplace<component::BoxModel>(entity);
    auto &text = registry.emplace<component::Text>(entity);
    auto &texture = registry.emplace<component::Texture2D>(entity);
    auto &transform = registry.emplace<component::Transform>(entity);

    text.colour = foregroundColour;
    text.value = textString;
    text.pFont = TTF_OpenFont(("../resources/open-sans/"+fontName).c_str(), fontSize);

    boxModel.border = border;
    boxModel.padding = padding;

    int width, height;
    TTF_SizeText(text.pFont, text.value.c_str(), &width, &height);

    transform.viewPort = {
        x,
        y,
        width + int(padding.left + padding.right + border.left + border.right),
        height + int(padding.top + padding.bottom + border.top + border.bottom)
    };

    auto pSurface = TTF_RenderText_Blended(text.pFont, text.value.c_str(), text.colour);
    auto pLabelTexture = SDL_CreateTextureFromSurface(&renderer, pSurface);
    SDL_FreeSurface(pSurface);

    texture.pTexture = SDL_CreateTexture(
        &director->getRenderer(),
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        transform.viewPort.w,
        transform.viewPort.h
    );
    texture.backgroundColour = backgroundColour;
    SDL_SetRenderTarget(&renderer, texture.pTexture);
    SDL_SetRenderDrawColor(&renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
    SDL_RenderClear(&renderer);
    SDL_Rect rect {int(padding.left+border.left), int(padding.top+border.top), width, height};
    SDL_RenderCopy(&renderer, pLabelTexture, nullptr, &rect);
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
    for(int32 i=0; i<std::max({border.bottom, border.left, border.right, border.top}); ++i) {
        if(i<border.bottom) SDL_RenderDrawLine(&renderer, 0, transform.viewPort.h - i, transform.viewPort.w, transform.viewPort.h - i);
        if(i<border.left) SDL_RenderDrawLine(&renderer, i, 0, i, transform.viewPort.h);
        if(i<border.right) SDL_RenderDrawLine(&renderer, transform.viewPort.w - i, 0, transform.viewPort.w - i, transform.viewPort.h);
        if(i<border.top) SDL_RenderDrawLine(&renderer, 0, i, transform.viewPort.w, i);
    }
    SDL_SetRenderTarget(&renderer, nullptr);

    return entity;
}
