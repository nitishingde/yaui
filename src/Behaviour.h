#ifndef YAUI_BEHAVIOUR_H
#define YAUI_BEHAVIOUR_H


#include "Types.h"

namespace yaui {
    class Behaviour {
    private:
        BehaviourUpdateFunctionPointer mpUpdateHandle = nullptr;
    public:
        String name;
        bool isEnabled = true;

    public:
        explicit Behaviour(String name, BehaviourUpdateFunctionPointer pUpdateFunctionPointer = nullptr) noexcept;
        void setUpdateHandle(BehaviourUpdateFunctionPointer pUpdateFunctionPointer);
        void update(entity::Registry &registry, const entity::Entity &entity, float delta) const;
    };
}


#endif //YAUI_BEHAVIOUR_H
