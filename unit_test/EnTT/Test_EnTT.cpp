#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include "entt/entt.hpp"
#include <iostream>

TEST_CASE("Initialization of EnTT", "[init]") {
    entt::registry *reg = new entt::registry();
    CHECK(reg != nullptr);
    delete reg;
}