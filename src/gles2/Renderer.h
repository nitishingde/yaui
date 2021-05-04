#ifndef YAUI_RENDERER_H
#define YAUI_RENDERER_H


#include <glm/glm.hpp>
#include <memory>
#include "Buffer.h"
#include "Window.h"

namespace yaui::gles2 {
    class Renderer {
    private:
        glm::mat4 mModelMatrix = glm::mat4(1.0f);
        glm::mat4 mViewMatrix = glm::mat4(1.0f);
        std::shared_ptr<gles2::Window> mpWindow = nullptr;

    public:
        explicit Renderer(std::shared_ptr<Window> pWindow);
        [[nodiscard]] std::shared_ptr<Window> getWindow() const;
        [[nodiscard]] glm::mat4 getMVP_Matrix() const;
        void enableBlend() const;
        void clearScreen(float r, float g, float b, float a) const;
        void drawElements(const VertexArrayBuffer &vertexArrayBuffer) const;
        void render() const;
    };
}


#endif //YAUI_RENDERER_H
