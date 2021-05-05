#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include <glm/glm.hpp>
#include <memory>
#include "Scene.h"

namespace yaui {
    class Director {
    private:
        std::vector<std::shared_ptr<gles2::Window>> mWindows;
        std::vector<std::shared_ptr<Scene>> mSceneStack;

    private:
        explicit Director() = default;
        bool init();

    public:
        ~Director();
        static Director *getInstance();
        void quit();
        void pushScene(std::shared_ptr<Scene> pScene);
        void popScene();
    };
}


#endif //YAUI_DIRECTOR_H
