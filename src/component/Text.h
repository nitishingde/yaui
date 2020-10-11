#ifndef YAUI_COMPONENT_TEXT_H
#define YAUI_COMPONENT_TEXT_H


#include "Types.h"

namespace yaui::component {
    struct Text {
        Colour colour {0, 0, 0, 255};
        String value;
        Font *pFont = nullptr;
        explicit Text() = default;
        Text(Text &&other) noexcept;
        Text& operator=(Text &&other) noexcept;
        ~Text();
    };
}


#endif //YAUI_COMPONENT_TEXT_H
