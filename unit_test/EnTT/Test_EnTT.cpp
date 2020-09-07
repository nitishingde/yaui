#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include "entt/entt.hpp"
#include <iostream>

class Vec2 {
public:
    int x, y;
    Vec2() noexcept
        : x(0)
        , y(0) {
        std::cout<<"Vec2() called\n";
    }
    Vec2(int x, int y) noexcept
        : x(x)
        , y(y) {
        std::cout<<"Vec2("<<x<<", "<<y<<") called\n";
    }
    Vec2(const Vec2 &other) noexcept {
        this->x = other.x;
        this->y = other.y;
        std::cout<<"Vec2(const Vec2 &other("<<this->x<<", "<<this->y<<") ) called\n";
    }
    Vec2& operator=(const Vec2 &other) {
        this->x = other.x;
        this->y = other.y;
        std::cout<<"operator=&("<<other.x<<", "<<other.y<<")\n";
    }
    Vec2(Vec2 &&other) noexcept {
        this->x = other.x;
        this->y = other.y;
        std::cout<<"Vec2(Vec2 &&other("<<other.x<<", "<<other.y<<") ) called\n";
    }
    Vec2& operator=(Vec2 &&other) {
        this->x = other.x;
        this->y = other.y;
        std::cout<<"operator=&&("<<other.x<<", "<<other.y<<")\n";
    }
//    Vec2(Vec2 *other) {
//        this->x = other->x;
//        this->y = other=>y;
//        delete other;
//    }
//    Vec2* operator=(Vec2 *other) {
//        return other;
//    }
};

TEST_CASE("Initialization of EnTT", "[init]") {
    auto reg = new entt::registry();
    auto entity = reg->create();
    auto vec = Vec2(1, 2);
    auto pvec = new Vec2(9, 12);
    reg->emplace_or_replace<Vec2*>(entity, new Vec2(6, 8));
    reg->emplace_or_replace<Vec2*>(entity, pvec);
    reg->emplace_or_replace<Vec2>(entity, Vec2(3, 4));
    reg->emplace_or_replace<Vec2>(entity, vec);
    reg->emplace_or_replace<Vec2>(entity, 9, 12);
//    reg->emplace_or_replace<Vec2>(entity, &vec);
    std::cout<<"cleanup\n";
    CHECK(reg != nullptr);
    reg->remove_all(entity);
    delete reg;
}