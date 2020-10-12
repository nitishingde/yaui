#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include "Types.h"
#include "Scene.h"

namespace yaui {
    class Director {
    private:
        bool mEngineIgnitionOn = true;
        Renderer *mpRenderer = nullptr;
        Window *mpWindow = nullptr;
        ArrayList<Scene*> mSceneStack;

    private:
        explicit Director();
        bool init();
    public:
        ~Director();
        static Director* getInstance();
        [[nodiscard]] float getDelta() const;
        [[nodiscard]] Renderer& getRenderer() const;
        [[nodiscard]] Scene& getScene() const;
        void popScene();
        void pushScene(Scene *pScene);
        void quit();
        void run();
    };
}


#endif //YAUI_DIRECTOR_H
