#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "yaui.h"
#include "catch2/catch.hpp"

TEST_CASE("Testing Vector2", "[Vector2]") {
    yaui::Vector2<yaui::int32> vector1;
    CHECK(vector1.mX == 0);
    CHECK(vector1.mY == 0);

    yaui::Vector2<float> vector2(12, 16);
    CHECK(vector2.mX == 12);
    CHECK(vector2.mY == 16);
}

TEST_CASE("Testing Window Getters", "[Window]") {
    auto window = yaui::system::Window("unit test");
    window.setDimension(640, 480);

    for(yaui::int32 i=0; i<1000; i++)
        window.run();

    CHECK(window.getWidth() == 640);
    CHECK(window.getHeight() == 480);
    auto dimension = window.getDimension();
    CHECK(dimension.mX == 640);
    CHECK(dimension.mY == 480);
}