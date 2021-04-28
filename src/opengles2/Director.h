#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include "Types.h"

namespace yaui {
    class Director {
    private:
        Window *mpWindow = nullptr;
        SDL_GLContext mGlContext = nullptr;
    private:
        explicit Director() = default;
        bool init();

    public:
        ~Director();
        static Director *getInstance();
        void quit();
        Window* getWindow() const;
    };
}


#endif //YAUI_DIRECTOR_H
