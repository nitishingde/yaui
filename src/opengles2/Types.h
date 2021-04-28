#ifndef YAUI_TYPES_H
#define YAUI_TYPES_H


#include <SDL.h>
#include <string>
#include <vector>

namespace yaui {
    using int8 = int8_t;
    using uint8 = uint8_t;
    using int16 = int16_t;
    using uint16 = uint16_t;
    using int32 = int32_t;
    using uint32 = uint32_t;
    using int64 = int64_t;
    using uint64 = uint64_t;

    using String = std::string;
    using Window = SDL_Window;
}


#endif //YAUI_TYPES_H
