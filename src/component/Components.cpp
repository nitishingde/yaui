#include "Components.h"
#include <iostream>

void yaui::component::BehaviourTraits::trigger() {
    isTriggered = true;
}

void
yaui::component::MouseEventListener::onButtonDown(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event)const {
    if(pOnButtonDownHandle) {
        pOnButtonDownHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onButtonUp(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnButtonUpHandle) {
        pOnButtonUpHandle(registry, entity, event);
    }
}

void yaui::component::MouseEventListener::onClick(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnClickHandle) {
        pOnClickHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onHoverEnter(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnHoverEnterHandle) {
        pOnHoverEnterHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onHoverLeave(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnHoverLeaveHandle) {
        pOnHoverLeaveHandle(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onScroll(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(pOnScrollHandle) {
        pOnScrollHandle(registry, entity, event);
    }
}

yaui::component::Text::Text(yaui::component::Text &&other) noexcept
    : colour(other.colour)
    , value(std::move(other.value))
    , pFont(other.pFont) {
    other.pFont = nullptr;
    std::cout<<"MOVED| component::Text\n";
}

yaui::component::Text& yaui::component::Text::operator=(yaui::component::Text &&other) noexcept {
    if(this != &other) {
        colour = other.colour;
        value = std::move(other.value);
        pFont = other.pFont;
        other.pFont = nullptr;
        std::cout<<"MOVE_ASSIGNED| component::Text\n";
    }
    return *this;
}

yaui::component::Text::~Text() {
    if(pFont) {
        TTF_CloseFont(pFont);
        pFont = nullptr;
        std::cout<<"DELETED| component::Text\n";
    }
}

yaui::component::Texture2D::Texture2D(yaui::component::Texture2D &&other) noexcept
    : backgroundColour(other.backgroundColour)
    , zIndex(other.zIndex)
    , pTexture(other.pTexture) {
    other.pTexture = nullptr;
    std::cout<<"MOVED| component::Texture2D\n";
}

yaui::component::Texture2D& yaui::component::Texture2D::operator=(yaui::component::Texture2D &&other) noexcept {
    if(this != &other) {
        this->backgroundColour = other.backgroundColour;
        this->zIndex = other.zIndex;
        this->pTexture = other.pTexture;
        other.pTexture = nullptr;
        std::cout<<"MOVE_ASSIGNED| component::Texture2D\n";
    }
    return *this;
}

yaui::component::Texture2D::~Texture2D() {
    if(pTexture) {
        SDL_DestroyTexture(pTexture);
        pTexture = nullptr;
        std::cout<<"DELETED| component::Texture2D\n";
    }
}
