#ifndef YAUI_BEHAVIOUR_H
#define YAUI_BEHAVIOUR_H


#include "Types.h"

namespace yaui {
    class Behaviour {
    private:
        UpdateFunctionPointer mpUpdateHandle = nullptr;
    public:
        String name;

    public:
        explicit Behaviour(String name, UpdateFunctionPointer pUpdateFunctionPointer = nullptr) noexcept;
        void setUpdateHandle(UpdateFunctionPointer pUpdateFunctionPointer);
        void update(entity::Registry &registry, const entity::Entity &entity, float delta) const;
    };
}


#endif //YAUI_BEHAVIOUR_H