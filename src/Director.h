#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include <glm/glm.hpp>
#include "opengles2/Renderer.h"
#include "Types.h"

namespace yaui {
    class Director {
    private:
        Window *mpWindow = nullptr;
        SDL_GLContext mGlContext = nullptr;
        Renderer mRenderer;
        glm::mat4 mModel = glm::mat4(1.0f);
        glm::mat4 mView = glm::mat4(1.0f);
        glm::mat4 mProjection = glm::mat4(1.0f);

    private:
        explicit Director() = default;
        bool init();

    public:
        ~Director();
        static Director *getInstance();
        void quit();
        Window* getWindow() const;
        [[nodiscard]] std::tuple<float, float> getWindowSize() const;
        Renderer getRenderer();
        glm::mat4 getMVP_Matrix();
    };
}


#endif //YAUI_DIRECTOR_H
