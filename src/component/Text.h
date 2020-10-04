#ifndef YAUI_COMPONENT_TEXT_H
#define YAUI_COMPONENT_TEXT_H


#include "Types.h"
#include "SDL_ttf.h"

namespace yaui::component {
    struct Text {
        Colour colour {0, 0, 0, 255};
        String value;
        TTF_Font *pFont = nullptr;
        explicit Text() = default;
        Text(Text &&other) noexcept;
        Text& operator=(Text &&other) noexcept;
        ~Text();
    };
}


#endif //YAUI_COMPONENT_TEXT_H
