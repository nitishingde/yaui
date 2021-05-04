#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"

const char* yaui::gles2::WindowCreationException::what() const noexcept {
    return "error while initialising a window";
}

yaui::gles2::Window::Window(const char *pName, int32 x, int32 y, int32 width, int32 height, bool borderless, bool resizable, bool hidden) {
    uint32 windowFlag = SDL_WINDOW_OPENGL;
    if(borderless) windowFlag |= SDL_WINDOW_BORDERLESS;
    if(resizable) windowFlag |= SDL_WINDOW_RESIZABLE;
    if(hidden) windowFlag |= SDL_WINDOW_HIDDEN;
    else windowFlag |= SDL_WINDOW_SHOWN;
    mpWindow = SDL_CreateWindow(
        pName,
        x,
        y,
        width,
        height,
        windowFlag
    );
    if(mpWindow == nullptr) throw WindowCreationException();

    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_PROFILE_MASK, SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(0);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCELERATED_VISUAL, 1);
    mpGlContext = SDL_GL_CreateContext(mpWindow);
    if(mpGlContext == nullptr) throw WindowCreationException();

    mProjectionMatrix = glm::ortho(0.f, float(width), 0.f, float(height));
}

yaui::gles2::Window::~Window() {
    SDL_GL_DeleteContext(mpGlContext);
    SDL_DestroyWindow(mpWindow);
}

void yaui::gles2::Window::setName(const char *pName) const {
    SDL_SetWindowTitle(mpWindow, pName);
}

std::tuple<yaui::int32, yaui::int32> yaui::gles2::Window::getSize() const {
    int32 width = 0, height = 0;
    SDL_GetWindowSize(mpWindow, &width, &height);
    return std::tuple<int32, int32>(width, height);
}

void yaui::gles2::Window::setSize(yaui::int32 width, yaui::int32 height) {
    SDL_SetWindowSize(mpWindow, width, height);
    mProjectionMatrix = glm::ortho(0.f, float(width), 0.f, float(height));
}

glm::mat4 yaui::gles2::Window::getProjectionMatrix() const {
    return mProjectionMatrix;
}

void yaui::gles2::Window::render() const {
    SDL_GL_MakeCurrent(mpWindow, mpGlContext);
    SDL_GL_SwapWindow(mpWindow);
}
