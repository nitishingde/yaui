#include "Components.h"
#include <spdlog/spdlog.h>

void
yaui::component::MouseEventListener::onButtonDown(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event)const {
    for(auto &eventListener: onButtonDownListeners) {
        eventListener(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onButtonUp(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    for(auto &eventListener: onButtonUpListeners) {
        eventListener(registry, entity, event);
    }
}

void yaui::component::MouseEventListener::onClick(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    for(auto &eventListener: onClickListeners) {
        eventListener(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onHoverEnter(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    for(auto &eventListener: onHoverEnterListeners) {
        eventListener(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onHoverLeave(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    for(auto &eventListener: onHoverLeaveListeners) {
        eventListener(registry, entity, event);
    }
}

void
yaui::component::MouseEventListener::onScroll(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    for(auto &eventListener: onScrollListeners) {
        eventListener(registry, entity, event);
    }
}

yaui::component::Text::Text(yaui::component::Text &&other) noexcept
    : colour(other.colour)
    , value(std::move(other.value))
    , pFont(other.pFont) {
    other.pFont = nullptr;
    spdlog::info("MOVED| component::Text");
}

yaui::component::Text& yaui::component::Text::operator=(yaui::component::Text &&other) noexcept {
    if(this != &other) {
        colour = other.colour;
        value = std::move(other.value);
        pFont = other.pFont;
        other.pFont = nullptr;
        spdlog::info("MOVE_ASSIGNED| component::Text");
    }
    return *this;
}

yaui::component::Text::~Text() {
    if(pFont) {
        TTF_CloseFont(pFont);
        pFont = nullptr;
        spdlog::info("DELETED| component::Text");
    }
}

void yaui::component::TextInputEventListener::onCharacterEntered(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(!isSelected) return;
    for(auto &eventListener: onCharacterEnteredListeners) {
        eventListener(registry, entity, event);
    }
}

void yaui::component::TextInputEventListener::onSpecialKeyPressed(yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) const {
    if(!isSelected) return;
    for(auto &eventListener: onSpecialKeyPressedListeners) {
        eventListener(registry, entity, event);
    }
}

yaui::component::Texture2D::Texture2D(yaui::component::Texture2D &&other) noexcept
    : backgroundColour(other.backgroundColour)
    , zIndex(other.zIndex)
    , pTexture(other.pTexture) {
    other.pTexture = nullptr;
    spdlog::info("MOVED| component::Texture2D");
}

yaui::component::Texture2D& yaui::component::Texture2D::operator=(yaui::component::Texture2D &&other) noexcept {
    if(this != &other) {
        this->backgroundColour = other.backgroundColour;
        this->zIndex = other.zIndex;
        this->pTexture = other.pTexture;
        other.pTexture = nullptr;
        spdlog::info("MOVE_ASSIGNED| component::Texture2D");
    }
    return *this;
}

yaui::component::Texture2D::~Texture2D() {
    if(pTexture) {
        SDL_DestroyTexture(pTexture);
        pTexture = nullptr;
        spdlog::info("DELETED| component::Texture2D");
    }
}

void yaui::component::TextureTransformationJobs::trigger() {
    isTriggered = true;
}
