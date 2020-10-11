#ifndef YAUI_SCENE_H
#define YAUI_SCENE_H


#include "Types.h"

namespace yaui {
    class Scene {
    private:
        String mName;
        entity::Registry mRegistry;
    public:
        explicit Scene(String name) noexcept;
        Scene(Scene &other) = delete;
        Scene& operator=(Scene &other) = delete;
        Scene(Scene &&other) noexcept;
        Scene& operator=(Scene &&other) noexcept;
        ~Scene();
        entity::Registry& getRegistry();
    };
}


#endif //YAUI_SCENE_H
