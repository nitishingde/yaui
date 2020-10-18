#ifndef YAUI_SYSTEMJOBSCHEDULAR_H
#define YAUI_SYSTEMJOBSCHEDULAR_H


#include "system/ISystem.h"
#include "Types.h"

namespace yaui {
    class SystemJobScheduler {
    private:
        ArrayList<system::ISystem*> mSystems;
        HashMap<String, system::ISystem*> mSystemStore;

    private:
        explicit SystemJobScheduler() = default;
        void init();
    public:
        ~SystemJobScheduler();
        static SystemJobScheduler* getInstance();
        void executeJobs();
        system::ISystem* getSystem(const String &systemName) const;
    };
}

#endif //YAUI_SYSTEMJOBSCHEDULAR_H
