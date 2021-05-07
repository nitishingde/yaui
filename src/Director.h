#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include <glm/glm.hpp>
#include <memory>
#include "Scene.h"
#include "system/SystemJobScheduler.h"

namespace yaui {
    class Director {
    private:
        std::vector<std::shared_ptr<gles2::Window>> mWindows;
        std::vector<std::shared_ptr<Scene>> mSceneStack;
        std::shared_ptr<system::SystemJobScheduler> mpSystemJobScheduler = nullptr;
        uint32 mFps = 60;
        uint32 mDelta = 0;
        bool mEngineIgnitionOn = true;

    private:
        explicit Director() = default;
        bool init();

    public:
        ~Director();
        static Director *getInstance();
        void run();
        void stop();
        void quit();
        void pushScene(const std::shared_ptr<Scene> &pScene);
        void popScene();
        void setFPS(uint32 fps);
    };
}


#endif //YAUI_DIRECTOR_H
