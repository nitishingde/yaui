#ifndef YAUI_ACTION_H
#define YAUI_ACTION_H


#include "Types.h"

namespace yaui {
    class Action {
    private:
        uint64 mCounter = 0;
        float mFixedDelay = 0;
        float mTimePassed = 0;
        ActionUpdateFunctionPointer mpActionUpdateHandle = nullptr;
    public:
        String name;

    public:
        explicit Action(String name = "", float fixedDelay = 1.f, ActionUpdateFunctionPointer pActionUpdateFunctionPointer = nullptr) noexcept;
        ~Action() noexcept;
        Action(const Action &other) noexcept;
        Action(Action &&other) noexcept;
        Action& operator=(const Action &other) noexcept;
        Action& operator=(Action &&other) noexcept;
        void setFixedDelay(float fixedDelay);
        void setUpdateHandle(ActionUpdateFunctionPointer pUpdateFunctionPointer);
        bool update(entity::Registry &registry, const entity::Entity &entity, float delta);
    };
}


#endif //YAUI_ACTION_H
