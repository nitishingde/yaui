#include "Renderer.h"
#include <SDL.h>
#include "Utility.h"

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
