#include "Components.h"
#include <spdlog/spdlog.h>
#include "EventDispatcher.h"

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

void
yaui::component::TextInputEventListener::registerListener(entity::Registry &registry, const entity::Entity &entity) {
    isSelected = true;
    EventDispatcher::getInstance()->registerListener(YAUI_TO_STRING(TextInputEventListener), registry, entity);
}

void
yaui::component::TextInputEventListener::unregisterListener(entity::Registry &registry, const entity::Entity &entity) {
    isSelected = false;
    EventDispatcher::getInstance()->unregisterListener(YAUI_TO_STRING(TextInputEventListener), registry, entity);
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
