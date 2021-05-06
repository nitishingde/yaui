#ifndef YAUI_SYSTEM_H
#define YAUI_SYSTEM_H


#include <entt/entity/registry.hpp>
#include "gles2/Renderer.h"
#include "gles2/Shader.h"
#include "Types.h"

namespace yaui::system {
    class ISystem {
    public:
        uint32 priorityRank = 0;

    public:
        virtual ~ISystem() = default;
        virtual void executeJob(entt::registry &registry, gles2::Renderer &renderer) = 0;
        bool operator<(const ISystem &other) const;
    };

    class RenderingBackgroundSystem: public ISystem {
    private:
        gles2::Shader mBackgroundShader{"background"};

    public:
        explicit RenderingBackgroundSystem(uint32 priorityRank);
        ~RenderingBackgroundSystem() override = default;
        void executeJob(entt::registry &registry, gles2::Renderer &renderer) override;
    };
};


#endif //YAUI_SYSTEM_H
