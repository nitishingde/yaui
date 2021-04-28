#ifndef YAUI_TYPES_H
#define YAUI_TYPES_H


#include <SDL.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <GLES2/gl2.h>

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
    template<typename key, typename value>
    using HashMap = std::unordered_map<key, value>;
    using Window = SDL_Window;

    struct Vec2 {
        float x;
        float y;
    } __attribute__((aligned(8)));

    struct Colour {
        float r;
        float g;
        float b;
        float a;
    } __attribute__((aligned(16)));

    struct BufferLayoutElement {
        String attribute;
        GLuint location;
        GLint size;
        GLenum type;
        GLint isNormalised;
        uint32 offset;
    } __attribute__((aligned(64)));
    using BufferLayout = std::vector<BufferLayoutElement>;
}


#endif //YAUI_TYPES_H
