#ifndef YAUI_TYPES_H
#define YAUI_TYPES_H


#include <cstdint>
#include "entt/entity/entity.hpp"
#include "entt/entity/registry.hpp"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

namespace yaui {
    using int8 = int8_t;
    using uint8 = uint8_t;
    using int16 = int16_t;
    using uint16 = uint16_t;
    using int32 = int32_t;
    using uint32 = uint32_t;
    using int64 = int64_t;
    using uint64 = uint64_t;

    template<typename Type, typename Alloc = std::allocator<Type>>
    using ArrayList = std::vector<Type, Alloc>;
    using Colour = SDL_Color;
    using Event = SDL_Event;
    using Font = TTF_Font;
    using FVec2 = SDL_FPoint;
    using FViewPort = SDL_FRect;
    using Renderer = SDL_Renderer;
    using String = std::string;
    using Surface = SDL_Surface;
    using Texture = SDL_Texture;
    using Vec2 = SDL_Point;
    using ViewPort = SDL_Rect;
    using Window = SDL_Window;

    struct Size {
        uint32 height = 0;
        uint32 width = 0;
    };

    struct FSize {
        float height = 0;
        float width = 0;
    };

    struct Rect {
        uint32 bottom = 0;
        uint32 left = 0;
        uint32 right = 0;
        uint32 top = 0;
    };

    namespace entity {
        using Entity = entt::entity;
        using Registry = entt::registry;
    }

    using UpdateFunctionPointer = void(*)(entity::Registry &registry, const entity::Entity &entity, float delta);
}


#endif // YAUI_TYPES_H
