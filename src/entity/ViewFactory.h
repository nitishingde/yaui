#ifndef YAUI_ENTITY_VIEWFACTORY_H
#define YAUI_ENTITY_VIEWFACTORY_H


#include "Types.h"
#include "Scene.h"

namespace yaui::entity {
    class ViewFactory {
    public:
        static Entity produceLabel(
            Registry &registry,
            const String &textString,
            const String &fontName = "OpenSans-Regular.ttf",
            const uint32 &fontSize = 16,
            const Colour &foregroundColour = {255, 255, 255, 255},
            const Colour &backgroundColour = {0, 0, 0, 0},
            const Rect &padding = {0, 0, 0, 0},
            const Rect &border = {0, 0, 0, 0},
            const Colour &borderColour = {127, 127, 127, 127},
            const int32 &x = 0,
            const int32 &y = 0
        );

        static Entity produceButton(
            Registry &registry,
            const String &textString,
            const String &fontName = "OpenSans-Regular.ttf",
            const uint32 &fontSize = 16,
            const Colour &foregroundColour = {255, 255, 255, 255},
            const Colour &backgroundColour = {0, 0, 0, 0},
            const Rect &padding = {0, 0, 0, 0},
            const Rect &border = {0, 0, 0, 0},
            const Colour &borderColour = {127, 127, 127, 127},
            const int32 &x = 0,
            const int32 &y = 0
        );
    };
}

#endif //YAUI_ENTITY_VIEWFACTORY_H
