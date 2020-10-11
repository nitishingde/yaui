#ifndef YAUI_COMPONENT_BOXMODEL_H
#define YAUI_COMPONENT_BOXMODEL_H


#include "Types.h"

namespace yaui::component {
    struct BoxModel {
        Rect border {0, 0, 0, 0};
        Colour borderColour {0, 0, 0, 0};
        Rect padding {0, 0, 0, 0};
    };
}


#endif //YAUI_COMPONENT_BOXMODEL_H
