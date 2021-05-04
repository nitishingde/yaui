#ifndef YAUI_SCENE_H
#define YAUI_SCENE_H


#include <entt/entity/registry.hpp>
#include "gles2/Renderer.h"

namespace yaui {
    class Scene {
    private:
        std::string mName;
        std::vector<entt::registry> mRegistryStack;
        std::vector<gles2::Renderer> mRenderers;

    public:
        explicit Scene(const char *pName = "") noexcept;
        Scene(Scene &other) = delete;
        Scene& operator=(Scene &other) = delete;
        Scene(Scene &&other) noexcept;
        Scene& operator=(Scene &&other) noexcept;
        [[nodiscard]] std::string getName() const;
        entt::registry& getRegistry(uint32 idx = 0);
        gles2::Renderer& getRenderer(uint32 idx = 0);
        void setRenderer(gles2::Renderer &&renderer);//FIXME: make it private
    };
}


#endif //YAUI_SCENE_H
