#ifndef YAUI_COMPONENT_BEHAVIOURTRAITS_H
#define YAUI_COMPONENT_BEHAVIOURTRAITS_H


#include "Types.h"
#include "Behaviour.h"

namespace yaui::component {
    struct BehaviourTraits {
    public:
        bool isTriggered = true;
        ArrayList<Behaviour> behaviours;
        void trigger();
    };
}


#endif //YAUI_COMPONENT_BEHAVIOURTRAITS_H
