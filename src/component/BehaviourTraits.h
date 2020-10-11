#ifndef YAUI_COMPONENT_BEHAVIOURTRAITS_H
#define YAUI_COMPONENT_BEHAVIOURTRAITS_H


#include "Types.h"
#include "Behaviour.h"

namespace yaui::component {
    struct BehaviourTraits {
    public:
        bool isUpdated = false;
        ArrayList<Behaviour> behaviours;
    };
}


#endif //YAUI_COMPONENT_BEHAVIOURTRAITS_H
