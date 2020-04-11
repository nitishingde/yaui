cmake_minimum_required(VERSION 3.15)

add_executable(unit_test_sdl2 Test_SDL2.cpp)
target_link_libraries(unit_test_sdl2 SDL2::SDL2 SDL2::IMAGE SDL2::TTF)
