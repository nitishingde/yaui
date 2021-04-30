#ifndef YAUI_RENDERER_H
#define YAUI_RENDERER_H


#include <glm/glm.hpp>
#include "Buffer.h"

namespace yaui {
    class Renderer {
    public:
        void clearScreen(const glm::vec4 &colour) const;
        void drawElements(const VertexArrayBuffer &vertexArrayBuffer) const;
        void present(Window *window) const;
    };
}


#endif //YAUI_RENDERER_H
