#include "Window.h"

yaui::system::Window::Window(
    const yaui::String &title,
    const yaui::int32 &positionX,
    const yaui::int32 &positionY,
    const yaui::int32 &width,
    const yaui::int32 &height
) {
    SDL_Init(SDL_INIT_VIDEO);
    this->mpWindow = SDL_CreateWindow(
        title.c_str(),
        positionX,
        positionY,
        width,
        height,
        0
    );
    this->mpRenderer = SDL_CreateRenderer(this->mpWindow, -1, SDL_RENDERER_SOFTWARE);
    this->mpRegistry = new entt::registry();
}

yaui::system::Window::~Window() {
    SDL_DestroyRenderer(this->mpRenderer);
    SDL_DestroyWindow(this->mpWindow);
    SDL_Quit();
}

bool yaui::system::Window::Init() {
    return true;
}

void yaui::system::Window::PollInputs() {
    //TODO
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)) {
        this->mEventQueue.emplace_back(sdlEvent);
    }
}

void yaui::system::Window::Update() {
    //TODO
}

void yaui::system::Window::Render() {
    SDL_RenderClear(this->mpRenderer);
    SDL_RenderPresent(this->mpRenderer);
}

void yaui::system::Window::Run() {
    PollInputs();
    Update();
    Render();
}

yaui::int32 yaui::system::Window::GetPositionX() const {
    int x, y;
    SDL_GetWindowPosition(this->mpWindow, &x, &y);
    return x;
}

void yaui::system::Window::SetPositionX(const yaui::int32 &x) {
    SDL_SetWindowPosition(this->mpWindow, x, this->GetPositionY());
}

yaui::int32 yaui::system::Window::GetPositionY() const {
    int x, y;
    SDL_GetWindowPosition(this->mpWindow, &x, &y);
    return y;
}

void yaui::system::Window::SetPositionY(const yaui::int32 &y) {
    SDL_SetWindowPosition(this->mpWindow, this->GetPositionX(), y);
}

yaui::Vector2<yaui::int32> yaui::system::Window::GetPosition() {
    int x, y;
    SDL_GetWindowPosition(this->mpWindow, &x, &y);
    return yaui::Vector2<yaui::int32>(x, y);
}

void yaui::system::Window::SetPosition(const yaui::int32 &x, const yaui::int32 &y) {
    SDL_SetWindowPosition(this->mpWindow, x, y);
}

yaui::int32 yaui::system::Window::GetWidth() const {
    int width, height;
    SDL_GetWindowSize(this->mpWindow, &width, &height);
    return width;
}

void yaui::system::Window::SetWidth(const yaui::int32 &width) {
    SDL_SetWindowSize(this->mpWindow, width, this->GetHeight());
}

yaui::int32 yaui::system::Window::GetHeight() const {
    int width, height;
    SDL_GetWindowSize(this->mpWindow, &width, &height);
    return height;
}

void yaui::system::Window::SetHeight(const yaui::int32 &height) {
    SDL_SetWindowSize(this->mpWindow, this->GetWidth(), height);
}

yaui::Vector2<yaui::int32> yaui::system::Window::GetDimension() {
    int width, height;
    SDL_GetWindowSize(this->mpWindow, &width, &height);
    return yaui::Vector2<yaui::int32>(width, height);
}

void yaui::system::Window::SetDimension(const yaui::int32 &width, const yaui::int32 &height) {
    SDL_SetWindowSize(this->mpWindow, width, height);
}
