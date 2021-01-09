#include "Components.h"
#include "LoggerConstants.h"

bool yaui::component::FocusEventListener::isInFocus() const {
    return isEnabled and isFocused;
}

void
yaui::component::KeyboardEventListener::registerListener(yaui::entity::Registry &registry, const yaui::entity::Entity &entity) {
    auto &keyboardEventState = registry.ctx_or_set<KeyboardEventState>();
    keyboardEventState.listeners.insert(entity);
}

void
yaui::component::KeyboardEventListener::unregisterListener(yaui::entity::Registry &registry, const yaui::entity::Entity &entity) {
    auto &keyboardEventState = registry.ctx_or_set<KeyboardEventState>();
    keyboardEventState.listeners.erase(entity);
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

void yaui::component::MouseEventState::resizeMouseMotionTracking() {
    if(mMotionTrackingQueue.size() > kMotionTrackingLimit) {
        mMotionTrackingQueue.erase(mMotionTrackingQueue.begin(), mMotionTrackingQueue.end()-kMotionTrackingLimit);
    }
}

void yaui::component::MouseEventState::reset() {
    for(auto &targetButtonEvents: mButtonEvents) {
        targetButtonEvents.release();
    }
    mMotionTrackingQueue.clear();
    previousTargetEntity = currentTargetEntity;
    currentTargetEntity = entity::null;
}

yaui::Vec2 yaui::component::MouseEventState::getCurrentMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return Vec2 {x, y};
}

yaui::Vec2 yaui::component::MouseEventState::getCurrentGlobalMousePosition() {
    int x, y;
    SDL_GetGlobalMouseState(&x, &y);
    return Vec2 {x, y};
}

const std::unique_ptr<yaui::TargetedEvent>& yaui::component::MouseEventState::getButtonTargetedEvent(yaui::component::MouseEventState::ButtonEventType type) const {
    mButtonEvents[type];
}

const yaui::ArrayList<yaui::TargetedEvent>& yaui::component::MouseEventState::getMotionTrackingQueue() {
    resizeMouseMotionTracking();
    return mMotionTrackingQueue;
}

void yaui::component::MouseEventState::setButtonEventDetails(const yaui::Event &event, yaui::entity::Entity targetEntity) {
    switch(event.type) {
        case EventType::SDL_MOUSEBUTTONDOWN:
            switch(event.button.button) {
                case SDL_BUTTON_LEFT:
                    mButtonEvents[ButtonEventType::LEFT_DOWN] = std::make_unique<TargetedEvent>(event, targetEntity);
                    break;

                case SDL_BUTTON_MIDDLE:
                    mButtonEvents[ButtonEventType::MIDDLE_DOWN] = std::make_unique<TargetedEvent>(event, targetEntity);
                    break;

                case SDL_BUTTON_RIGHT:
                    mButtonEvents[ButtonEventType::RIGHT_DOWN] = std::make_unique<TargetedEvent>(event, targetEntity);
                    break;
            }
            break;

        case EventType::SDL_MOUSEBUTTONUP:
            switch(event.button.button) {
                case SDL_BUTTON_LEFT:
                    mButtonEvents[ButtonEventType::LEFT_UP] = std::make_unique<TargetedEvent>(event, targetEntity);
                    break;

                case SDL_BUTTON_MIDDLE:
                    mButtonEvents[ButtonEventType::MIDDLE_UP] = std::make_unique<TargetedEvent>(event, targetEntity);
                    break;

                case SDL_BUTTON_RIGHT:
                    mButtonEvents[ButtonEventType::RIGHT_UP] = std::make_unique<TargetedEvent>(event, targetEntity);
                    break;
            }
            break;

        case EventType::SDL_MOUSEMOTION:
            if(mMotionTrackingQueue.size() > kMotionTrackingLimit*4) {
                resizeMouseMotionTracking();
            }
            mMotionTrackingQueue.emplace_back(TargetedEvent {event, targetEntity});
            break;

        case EventType::SDL_MOUSEWHEEL:
            if(pScrollTargetedEvent == nullptr) {
                pScrollTargetedEvent = std::make_unique<TargetedEvent>(event, targetEntity);
            } else {
                int32 x = pScrollTargetedEvent->event.wheel.x, y = pScrollTargetedEvent->event.wheel.y;
                pScrollTargetedEvent->event = event;
                pScrollTargetedEvent->event.wheel.x += x;
                pScrollTargetedEvent->event.wheel.y += y;
            }
            break;
    }
}
