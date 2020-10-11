#ifndef YAUI_BEHAVIOURFACTORY_H
#define YAUI_BEHAVIOURFACTORY_H


#include "Behaviour.h"

namespace yaui {
    class BehaviourFactory {
    public:
        static Behaviour produceAddBackgroundColourBehaviour();
        static Behaviour produceAddBorderBehaviour();
        static Behaviour produceAddTextBehaviour();
    };
}


#endif //YAUI_BEHAVIOURFACTORY_H
