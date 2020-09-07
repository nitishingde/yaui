#include "Window.h"
#include "Director.h"
#include "../component/Transform.h"

yaui::system::Window::Window(
    const yaui::String &title,
    const yaui::int32 &positionX,
    const yaui::int32 &positionY,
    const yaui::int32 &width,
    const yaui::int32 &height
) {
    if(!Director::getInstance()->init()) return;

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

bool yaui::system::Window::init() {
    return true;
}

void yaui::system::Window::pollInputs() {
    //TODO
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)) {
        this->mEventQueue.emplace_back(sdlEvent);
    }
}

void yaui::system::Window::update() {
    //TODO
}

void yaui::system::Window::render() {
    SDL_RenderClear(this->mpRenderer);
    this->mpRegistry->view<SDL_Texture*>().each([this](auto texture) {
        SDL_RenderCopy(this->mpRenderer, texture, nullptr, nullptr);
    });
    SDL_RenderPresent(this->mpRenderer);
}

void yaui::system::Window::run() {
    pollInputs();
    update();
    render();
}

yaui::int32 yaui::system::Window::getPositionX() const {
    int x, y;
    SDL_GetWindowPosition(this->mpWindow, &x, &y);
    return x;
}

void yaui::system::Window::setPositionX(const yaui::int32 &x) {
    SDL_SetWindowPosition(this->mpWindow, x, this->getPositionY());
}

yaui::int32 yaui::system::Window::getPositionY() const {
    int x, y;
    SDL_GetWindowPosition(this->mpWindow, &x, &y);
    return y;
}

void yaui::system::Window::setPositionY(const yaui::int32 &y) {
    SDL_SetWindowPosition(this->mpWindow, this->getPositionX(), y);
}

yaui::Vector2<yaui::int32> yaui::system::Window::getPosition() {
    int x, y;
    SDL_GetWindowPosition(this->mpWindow, &x, &y);
    return yaui::Vector2<yaui::int32>(x, y);
}

void yaui::system::Window::setPosition(const yaui::int32 &x, const yaui::int32 &y) {
    SDL_SetWindowPosition(this->mpWindow, x, y);
}

yaui::int32 yaui::system::Window::getWidth() const {
    int width, height;
    SDL_GetWindowSize(this->mpWindow, &width, &height);
    return width;
}

void yaui::system::Window::setWidth(const yaui::int32 &width) {
    SDL_SetWindowSize(this->mpWindow, width, this->getHeight());
}

yaui::int32 yaui::system::Window::getHeight() const {
    int width, height;
    SDL_GetWindowSize(this->mpWindow, &width, &height);
    return height;
}

void yaui::system::Window::setHeight(const yaui::int32 &height) {
    SDL_SetWindowSize(this->mpWindow, this->getWidth(), height);
}

yaui::Vector2<yaui::int32> yaui::system::Window::getDimension() {
    int width, height;
    SDL_GetWindowSize(this->mpWindow, &width, &height);
    return yaui::Vector2<yaui::int32>(width, height);
}

void yaui::system::Window::setDimension(const yaui::int32 &width, const yaui::int32 &height) {
    SDL_SetWindowSize(this->mpWindow, width, height);
}

yaui::entity::ViewObject *yaui::system::Window::getViewObject() {
    auto entity = this->mpRegistry->create();
    this->mpRegistry->emplace<yaui::component::Transform*>(entity);
    auto viewObject = new yaui::entity::ViewObject(
        entity,
        this->mpRegistry
    );

    return viewObject;
}
