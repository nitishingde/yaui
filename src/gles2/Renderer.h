#ifndef YAUI_RENDERER_H
#define YAUI_RENDERER_H


#include <glm/glm.hpp>
#include "Buffer.h"

namespace yaui::gles2 {
    class Renderer {
    public:
        void enableBlend() const;
        void clearScreen(float r, float g, float b, float a) const;
        void drawElements(const VertexArrayBuffer &vertexArrayBuffer) const;
        void present(Window *window) const;
    };
}


#endif //YAUI_RENDERER_H
