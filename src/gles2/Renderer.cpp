#include "Renderer.h"
#include "Utility.h"

yaui::gles2::Renderer::Renderer(std::shared_ptr<yaui::gles2::Window> pWindow)
    : mpWindow(std::move(pWindow)) {
}

std::shared_ptr<yaui::gles2::Window> yaui::gles2::Renderer::getWindow() const {
    return mpWindow;
}

glm::mat4 yaui::gles2::Renderer::getMVP_Matrix() const {
    return mpWindow->getProjectionMatrix() * mViewMatrix * mModelMatrix;
}

void yaui::gles2::Renderer::enableBlend() const {
    // FIXME: hardcoded
    debugGlCall(glEnable(GL_BLEND));
    debugGlCall(glBlendEquation(GL_FUNC_ADD));
    debugGlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void yaui::gles2::Renderer::clearScreen(float r, float g, float b, float a) const {
    debugGlCall(glClearColor(r, g, b, a));
    debugGlCall(glClear(GL_COLOR_BUFFER_BIT));
}

void yaui::gles2::Renderer::drawElements(const yaui::gles2::VertexArrayBuffer &vertexArrayBuffer) const {
    debugGlCall(glDrawElements(GL_TRIANGLES, vertexArrayBuffer.getCount(), vertexArrayBuffer.getType(), nullptr));
}

void yaui::gles2::Renderer::render() const {
    mpWindow->render();
}
