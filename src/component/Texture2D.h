#ifndef YAUI_COMPONENT_RENDER_H
#define YAUI_COMPONENT_RENDER_H


#include "Types.h"

namespace yaui::component {
    struct Texture2D {
        Colour backgroundColour{0, 0, 0, 0};
        uint32 zIndex = 0;
        Texture *pTexture = nullptr;
        explicit Texture2D() = default;
        Texture2D(Texture2D &&other) noexcept;
        Texture2D& operator=(Texture2D &&other) noexcept;
        ~Texture2D();
    };
}


#endif //YAUI_COMPONENT_RENDER_H
