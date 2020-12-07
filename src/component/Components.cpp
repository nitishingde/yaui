#include "Components.h"
#include "EventDispatcher.h"
#include "LoggerConstants.h"

bool yaui::component::FocusEventListener::isInFocus() const {
    return isEnabled and isFocused;
}

yaui::component::Text::Text() noexcept {
    spdlog::info("{} {}", Logger::kConstructed, YAUI_TO_STRING(yaui::component::Text));
}

yaui::component::Text::Text(yaui::component::Text &&other) noexcept
    : colour(other.colour)
    , value(std::move(other.value))
    , pFont(other.pFont) {
    other.pFont = nullptr;
    spdlog::info("{} {}", Logger::kMoved, YAUI_TO_STRING(yaui::component::Text));
}

yaui::component::Text& yaui::component::Text::operator=(yaui::component::Text &&other) noexcept {
    if(this != &other) {
        colour = other.colour;
        value = std::move(other.value);
        pFont = other.pFont;
        other.pFont = nullptr;
        spdlog::info("{}{} {}", Logger::kMoved, Logger::kAssigned, YAUI_TO_STRING(yaui::component::Text));
    }
    return *this;
}

yaui::component::Text::~Text() {
    if(pFont) {
        TTF_CloseFont(pFont);
        pFont = nullptr;
    }
    spdlog::info("{} {}", Logger::kDestructed, YAUI_TO_STRING(yaui::component::Text));
}

yaui::component::TextInputEventListener::~TextInputEventListener() noexcept {
    EventDispatcher::getInstance()->unregisterListener(*this);
}

yaui::String yaui::component::TextInputEventListener::getClassName() const {
    return YAUI_TO_STRING(TextInputEventListener);
}

void
yaui::component::TextInputEventListener::registerListener(entity::Registry &registry, const entity::Entity &entity) {
    auto &textInputEventState = registry.ctx_or_set<component::TextInputEventState>();
    textInputEventState.listeners.insert(entity);
}

void
yaui::component::TextInputEventListener::unregisterListener(entity::Registry &registry, const entity::Entity &entity) {
    auto &textInputEventState = registry.ctx_or_set<component::TextInputEventState>();
    textInputEventState.listeners.erase(entity);
}

yaui::component::Texture2D::Texture2D() noexcept {
    spdlog::info("{} {}", Logger::kConstructed, YAUI_TO_STRING(yaui::component::Texture2D));
}

yaui::component::Texture2D::Texture2D(yaui::component::Texture2D &&other) noexcept
    : backgroundColour(other.backgroundColour)
    , zIndex(other.zIndex)
    , pTexture(other.pTexture) {
    other.pTexture = nullptr;
    spdlog::info("{} {}", Logger::kMoved, YAUI_TO_STRING(yaui::component::Texture2D));
}

yaui::component::Texture2D& yaui::component::Texture2D::operator=(yaui::component::Texture2D &&other) noexcept {
    if(this != &other) {
        this->backgroundColour = other.backgroundColour;
        this->zIndex = other.zIndex;
        this->pTexture = other.pTexture;
        other.pTexture = nullptr;
        spdlog::info("{}{} {}", Logger::kMoved, Logger::kAssigned, YAUI_TO_STRING(yaui::component::Texture2D));
    }
    return *this;
}

yaui::component::Texture2D::~Texture2D() {
    if(pTexture) {
        SDL_DestroyTexture(pTexture);
        pTexture = nullptr;
    }
    spdlog::info("{} {}", Logger::kDestructed, YAUI_TO_STRING(yaui::component::Texture2D));
}

void yaui::component::TextureTransformationJobs::trigger() {
    isTriggered = true;
}
