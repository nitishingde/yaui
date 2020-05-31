cmake_minimum_required(VERSION 3.15)

add_executable(unit_test_entt Test_EnTT.cpp)
target_link_libraries(unit_test_entt
    PRIVATE
        EnTT::EnTT
        Catch2::Catch2
)
