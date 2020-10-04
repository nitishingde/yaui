#ifndef YAUI_SYSTEMJOBSCHEDULAR_H
#define YAUI_SYSTEMJOBSCHEDULAR_H


#include "system/ISystem.h"
#include "Types.h"

namespace yaui {
    class SystemJobScheduler {
    private:
        ArrayList<system::ISystem*> mSystems;

    private:
        explicit SystemJobScheduler();
        void init();
    public:
        static SystemJobScheduler* getInstance();
        void executeJobs();
    };
}

#endif //YAUI_SYSTEMJOBSCHEDULAR_H
