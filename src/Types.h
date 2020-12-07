#ifndef YAUI_TYPES_H
#define YAUI_TYPES_H


#include <cstdint>
#include <set>
#include "entt/entity/entity.hpp"
#include "entt/entity/registry.hpp"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#define YAUI_TO_STRING(x) #x
#define YAUI_USE_FUNCTION_POINTER 1

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
    using EventType = SDL_EventType;
    using Font = TTF_Font;
    using FVec2 = SDL_FPoint;
    using FViewPort = SDL_FRect;
    template<typename key, typename value>
    using HashMap = std::unordered_map<key, value>;
    using Renderer = SDL_Renderer;
    template<typename Type, typename Compare = std::less<Type>, typename Alloc = std::allocator<Type>>
    using Set = std::set<Type, Compare, Alloc>;
    using String = std::string;
    using Surface = SDL_Surface;
    using Texture = SDL_Texture;
    using Vec2 = SDL_Point;
    using ViewPort = SDL_Rect;
    using Window = SDL_Window;

    struct Size {
        uint32 width = 0;
        uint32 height = 0;
    };

    struct FSize {
        float width = 0;
        float height = 0;
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
        inline constexpr entt::null_t null{};
    }

    struct Object {
        [[nodiscard]] virtual String getClassName() const = 0;
    };

    using IEventListener = Object;

    // should return false to discontinue
#if YAUI_USE_FUNCTION_POINTER
    using ActionUpdateFunctionPointer = bool(*)(entity::Registry &registry, const entity::Entity &entity, float delay, uint64 counter);
    using BehaviourUpdateFunctionPointer = bool(*)(entity::Registry &registry, const entity::Entity &entity, float delay);
    using TextureTransformationUpdateFunctionPointer = void(*)(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta);
    using EventHandlerFunctionPointer = bool(*)(entity::Registry &registry, const entity::Entity &entity, const Event &event);
#else
    using ActionUpdateFunctionPointer = std::function<bool(entity::Registry &registry, const entity::Entity &entity, float delay, uint64 counter)>;
    using BehaviourUpdateFunctionPointer = std::function<bool(entity::Registry &registry, const entity::Entity &entity, float delay)>;
    using TextureTransformationUpdateFunctionPointer = std::function<void(Renderer &renderer, entity::Registry &registry, const entity::Entity &entity, float delta)>;
    using EventHandlerFunctionPointer = std::function<bool(entity::Registry &registry, const entity::Entity &entity, const Event &event)>;
#endif
}


#endif // YAUI_TYPES_H
