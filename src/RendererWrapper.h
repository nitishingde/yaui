#ifndef YAUI_RENDERERWRAPPER_H
#define YAUI_RENDERERWRAPPER_H


#include "Types.h"

namespace yaui {
    class RendererWrapper {
    private:
        Renderer *mpRenderer = nullptr;

    public:
        explicit RendererWrapper(Renderer *pRenderer) noexcept;
        RendererWrapper(RendererWrapper &&other) noexcept;
        RendererWrapper &operator=(RendererWrapper &&other) noexcept;
        RendererWrapper(const RendererWrapper &other) = delete;
        RendererWrapper &operator=(const RendererWrapper &other) = delete;
        ~RendererWrapper();
        Renderer& getRenderer();
    };
}


#endif //YAUI_RENDERERWRAPPER_H
