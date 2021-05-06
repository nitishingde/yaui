#ifndef YAUI_SYSTEM_SYSTEMJOBSCHEDULAR_H
#define YAUI_SYSTEM_SYSTEMJOBSCHEDULAR_H


#include <memory>
#include "System.h"
#include "Types.h"

namespace yaui::system {
    class SystemJobScheduler {
    private:
        std::vector<std::shared_ptr<ISystem>> mSystems;

    private:
        explicit SystemJobScheduler() = default;
        void init();
    public:
        ~SystemJobScheduler();
        static SystemJobScheduler* getInstance();
        void executeJobs(entt::registry &registry, gles2::Renderer &renderer);
    };
}

#endif //YAUI_SYSTEM_SYSTEMJOBSCHEDULAR_H
