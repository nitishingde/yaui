#ifndef YAUI_COMPONENT_TRANSFORM_H
#define YAUI_COMPONENT_TRANSFORM_H


#include "Types.h"

namespace yaui::component {
    struct Transform {
        ViewPort viewPort {0, 0, 0, 0};
        FVec2 scale {1.f, 1.f};
    };
}


#endif //YAUI_COMPONENT_TRANSFORM_H
