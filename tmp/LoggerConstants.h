#ifndef YAUI_LOGGERCONSTANTS_H
#define YAUI_LOGGERCONSTANTS_H


#include <spdlog/spdlog.h>
#include "Types.h"

namespace yaui::Logger {
    static const String kAssigned = "[ASSIGNED]";
    static const String kConstructed = "[CONSTRUCTED]";
    static const String kDestructed = "[DESTRUCTED]";
    static const String kInitialised = "[INITIALISED]";
    static const String kMoved = "[MOVED]";
    static const String kStats = "[STATS]";
}


#endif //YAUI_LOGGERCONSTANTS_H
