#include "Director.h"
#include "Utility.h"

static yaui::Director* instance = nullptr;

yaui::Director::~Director() {
    SDL_GL_DeleteContext(mGlContext);
    SDL_DestroyWindow(mpWindow);
    SDL_Quit();
}

yaui::Director *yaui::Director::getInstance() {
    if(instance == nullptr) {
        instance = new Director();
        if(!instance->init()) return nullptr;
    }
    return instance;
}

bool yaui::Director::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    mpWindow = SDL_CreateWindow(
        "YAUI - OpenGL ES 2.0",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1080,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if(mpWindow == nullptr) return false;

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

    mGlContext = SDL_GL_CreateContext(mpWindow);
    debugGlCall(auto glsl_v = glGetString(GL_SHADING_LANGUAGE_VERSION));
    debugGlCall(auto gl_v = glGetString(GL_VERSION));
    printf("GL version             : %s\n", gl_v);
    printf("GLSL version supported : %s\n", glsl_v);
    printf("-----------------------------------------------------------------------------\n");

    return true;
}

void yaui::Director::quit() {
    delete instance;
    instance = nullptr;
}

yaui::Window* yaui::Director::getWindow() const {
    return mpWindow;
}