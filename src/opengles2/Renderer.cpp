#include "Renderer.h"
#include <SDL.h>
#include "Utility.h"

void yaui::Renderer::enableBlend() const {
    // FIXME: hardcoded
    debugGlCall(glEnable(GL_BLEND));
    debugGlCall(glBlendEquation(GL_FUNC_ADD));
    debugGlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void yaui::Renderer::clearScreen(float r, float g, float b, float a) const {
    debugGlCall(glClearColor(r, g, b, a));
    debugGlCall(glClear(GL_COLOR_BUFFER_BIT));
}

void yaui::Renderer::drawElements(const yaui::VertexArrayBuffer &vertexArrayBuffer) const {
    debugGlCall(glDrawElements(GL_TRIANGLES, vertexArrayBuffer.getSize(), vertexArrayBuffer.getType(), nullptr));
}

void yaui::Renderer::present(Window *window) const {
    SDL_GL_SwapWindow(window);
}
