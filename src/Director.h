#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include "Types.h"
#include "Scene.h"

namespace yaui {
    class Director {
    private:
        bool mEngineIgnitionOn = true;
        uint64 mFps = 60;
        int32 mDelta = 0;
        ArrayList<Scene*> mSceneStack;
        Renderer *mpRenderer = nullptr;
        Window *mpWindow = nullptr;

    private:
        explicit Director();
        bool init();
    public:
        ~Director();
        static Director* getInstance();
        void disableStats();
        void enableStats();
        [[nodiscard]] float getDelta() const;
        [[nodiscard]] Renderer& getRenderer() const;
        [[nodiscard]] Scene& getScene() const;
        [[nodiscard]] Size getWindowSize() const;
        void popScene();
        void pushScene(Scene *pScene);
        void setFPS(uint32 fps);
        void quit();
        void run();
    };
}


#endif //YAUI_DIRECTOR_H
