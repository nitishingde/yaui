cmake_minimum_required(VERSION 3.15)

add_executable(unit_test_yaui Test_yaui.cpp)
target_link_libraries(unit_test_yaui
    PRIVATE
        Catch2::Catch2
        yaui::yaui
)
