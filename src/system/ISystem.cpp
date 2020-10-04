#include "ISystem.h"

bool yaui::system::ISystem::operator<(const yaui::system::ISystem &other) const {
    return this->mPriorityRank < other.mPriorityRank;
}
