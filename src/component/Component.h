#ifndef YAUI_COMPONENT_COMPONENT_H
#define YAUI_COMPONENT_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include "Types.h"

namespace yaui::component {
    struct Transform {
        glm::vec4 viewPort;
        glm::vec2 scale;
        glm::quat rotation;
        glm::vec4 colour;
    } __attribute__((aligned(64)));
}

#endif //YAUI_COMPONENT_COMPONENT_H