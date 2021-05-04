#include "Action.h"
#include "Director.h"

yaui::Action::Action(yaui::String name, float fixedDelay, yaui::ActionUpdateFunctionPointer pActionUpdateFunctionPointer) noexcept
    : name(std::move(name))
    , mFixedDelay(fixedDelay*1000.f)
    , mpActionUpdateHandle(pActionUpdateFunctionPointer) {
}

yaui::Action::~Action() noexcept {
    mpActionUpdateHandle = nullptr;
}

yaui::Action::Action(const yaui::Action &other) noexcept
    : mCounter(other.mCounter)
    , mFixedDelay(other.mFixedDelay)
    , mTimePassed(other.mTimePassed)
    , mpActionUpdateHandle(other.mpActionUpdateHandle)
    , name(other.name) {

}

yaui::Action::Action(yaui::Action &&other) noexcept
    : mCounter(other.mCounter)
    , mFixedDelay(other.mFixedDelay)
    , mTimePassed(other.mTimePassed)
    , mpActionUpdateHandle(other.mpActionUpdateHandle)
    , name(std::move(other.name)) {
    other.mpActionUpdateHandle = nullptr;
}

yaui::Action& yaui::Action::operator=(const yaui::Action &other) noexcept {
    if(this != &other) {
        this->mCounter = other.mCounter;
        this->mFixedDelay = other.mFixedDelay;
        this->mTimePassed = other.mTimePassed;
        this->mpActionUpdateHandle = other.mpActionUpdateHandle;
        this->name = other.name;
    }
    return *this;
}

yaui::Action& yaui::Action::operator=(yaui::Action &&other) noexcept {
    if(this != &other) {
        this->mCounter = other.mCounter;
        this->mFixedDelay = other.mFixedDelay;
        this->mTimePassed = other.mTimePassed;
        this->mpActionUpdateHandle = other.mpActionUpdateHandle;
        other.mpActionUpdateHandle = nullptr;
        this->name = std::move(other.name);
    }
    return *this;
}

void yaui::Action::setFixedDelay(float fixedDelay) {
    mFixedDelay = fixedDelay*1000;
}

void yaui::Action::setUpdateHandle(yaui::ActionUpdateFunctionPointer pUpdateFunctionPointer) {
    mpActionUpdateHandle = pUpdateFunctionPointer;
}

bool yaui::Action::update(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, float delta) {
    // reset when the handle is null
    if(!mpActionUpdateHandle) {
        mTimePassed = 0;
        return false;
    }

    mTimePassed += delta;
    if(mTimePassed < mFixedDelay) return true;

    mCounter++;
    auto val = mpActionUpdateHandle(registry, entity, mTimePassed/1000.f, mCounter);
    mTimePassed -= mFixedDelay;
    return val;
}
