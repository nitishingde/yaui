#ifndef YAUI_TYPES_H
#define YAUI_TYPES_H


#include <cstdint>
#include "Vector2.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/registry.hpp"
#include "SDL.h"

namespace yaui {
    using int8 = int8_t;
    using uint8 = uint8_t;
    using int16 = int16_t;
    using uint16 = uint16_t;
    using int32 = int32_t;
    using uint32 = uint32_t;
    using int64 = int64_t;
    using uint64 = uint64_t;
    using Dimension = Vector2<int32>;
    using Position = Vector2<int32>;
    template<typename Type>
    using ArrayList = std::vector<Type>;
    using String = std::string;

    using ViewPort = SDL_Rect;

    namespace entity {
        using Entity = entt::entity;
    }

    namespace component {

    }

    namespace system {
        using Registry = entt::registry;
    }
}


#endif // YAUI_TYPES_H