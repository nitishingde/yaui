#ifndef YAUI_UTILITY_H
#define YAUI_UTILITY_H


#include "Types.h"
#include "component/Components.h"

namespace yaui {
    Size getDimensionForText(const component::Text &text, component::BoxModel *pBoxModel = nullptr);
}


#endif //YAUI_UTILITY_H
