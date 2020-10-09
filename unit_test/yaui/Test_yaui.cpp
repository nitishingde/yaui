#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include "yaui.h"

using namespace yaui;

TEST_CASE("Test yaui", "[yaui][Label]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->pushScene(new Scene("Test yaui"));
    entity::ViewFactory::produceLabel(
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
    dir->run();
}