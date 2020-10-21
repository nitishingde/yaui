#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include "yaui.h"

using namespace yaui;

TEST_CASE("Test yaui", "[yaui]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->pushScene(new Scene("Test yaui"));
    dir->run();
}

TEST_CASE("Test yaui Label", "[yaui][Label]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->disableStats();
    dir->setFPS(60);
    dir->pushScene(new Scene("Test yaui"));
    auto labelEntity = entity::ViewFactory::produceLabel(
        dir->getScene(),
        "Hello World!",
        "OpenSans-Regular.ttf",
        32,
        {255, 255, 255, 255},
        {255, 0, 0, 0},
        {0, 10 , 10, 0},
        {5, 5 , 5, 5},
        40,
        30
    );
    auto &registry = dir->getScene().getRegistry();
    auto &actionItems = registry.emplace<component::ActionItems>(labelEntity);
    actionItems.actions.emplace_back(Action(
        "DiscoBackground",
        1.f,
        [](entity::Registry &registry, const entity::Entity &entity, float delay, uint64 counter) {
            auto [texture2D, behaviourTraits] = registry.get<component::Texture2D, component::BehaviourTraits>(entity);
            texture2D.backgroundColour.g = (texture2D.backgroundColour.g+32)%256;
            texture2D.backgroundColour.b = (texture2D.backgroundColour.b+32)%256;
            texture2D.backgroundColour.a = (texture2D.backgroundColour.a+32)%256;
            behaviourTraits.isUpdated = false;
            std::cout<<"DiscoBackground (Delay, Counter) ("<<delay<<", "<<counter<<")\n";
            return true;
        }
    ));
    dir->run();
}

TEST_CASE("Test yaui Button", "[yaui][Button]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->enableStats();
    dir->setFPS(60);
    dir->pushScene(new Scene("Test yaui"));
    auto entity = entity::ViewFactory::produceButton(
        dir->getScene(),
        "Hello World!",
        "OpenSans-Regular.ttf",
        32,
        {255, 255, 255, 255},
        {255, 0, 0, 127},
        {0, 10 , 10, 0},
        {5, 5 , 5, 5},
        40,
        30
    );
    auto &registry = dir->getScene().getRegistry();
    auto &mouseEventListener = registry.get<component::MouseEventListener>(entity);
    mouseEventListener.pOnClickHandle = [](yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) {
        auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;
        backgroundColour.g = (backgroundColour.g+64)%256;
        registry.get<component::BehaviourTraits>(entity).isUpdated = false;
    };
    mouseEventListener.pOnHoverEnterHandle = [](yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) {
        auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;
        backgroundColour.b = 255;
        registry.get<component::BehaviourTraits>(entity).isUpdated = false;
    };
    mouseEventListener.pOnHoverLeaveHandle = [](yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) {
        auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;
        backgroundColour.b = 0;
        registry.get<component::BehaviourTraits>(entity).isUpdated = false;
    };
    dir->run();
}