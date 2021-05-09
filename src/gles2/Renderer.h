#ifndef YAUI_GLES2_RENDERER_H
#define YAUI_GLES2_RENDERER_H


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
        ~Renderer() = default;
        Renderer(const Renderer &other) = delete;
        Renderer& operator=(const Renderer &other) = delete;
        Renderer(Renderer &&other) = default;
        Renderer& operator=(Renderer &&other) = default;
        [[nodiscard]] std::shared_ptr<Window> getWindow() const;
        [[nodiscard]] glm::mat4 getMVP_Matrix() const;
        void enableBlend() const;
        void clearScreen(float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f) const;
        void drawElements(const VertexArrayBuffer &vertexArrayBuffer) const;
        void render() const;
    };
}


#endif //YAUI_GLES2_RENDERER_H
