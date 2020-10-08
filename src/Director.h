#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include "Types.h"

namespace yaui {
    class Director {
    private:
        entity::Registry mRegistry;
        Renderer *mpRenderer;
        Window *mpWindow;

    private:
        explicit Director();
        bool init();
    public:
        ~Director();
        static Director* getInstance();
        entity::Registry& getRegistry();
        Renderer* getRenderer();
        Window& getWindow();
        Size getWindowSize() const;
        void run();
    };
}


#endif //YAUI_DIRECTOR_H
