#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


#include "Types.h"

namespace yaui {
    class Director {
    private:
        entity::Registry mRegistry;
        Window *mpWindow;
        Renderer *mpRenerer;

    private:
        explicit Director();
        bool init();
    public:
        ~Director();
        static Director* getInstance();
        entity::Registry& getRegistry();
        Window& getWindow();
        Renderer* getRenderer();
        Size getWindowSize() const;
        void run();
        void destroy();
    };
}


#endif //YAUI_DIRECTOR_H
