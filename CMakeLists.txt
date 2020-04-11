cmake_minimum_required(VERSION 3.15)
project(yaui)

add_definitions(
    -std=c++14
)

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

# 3rd party libraries: SDL2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL2_ttf)

add_executable(test_SDL2 ${PROJECT_SOURCE_DIR}/test/Test_SDL2.cpp)
target_link_libraries(test_SDL2 SDL2::SDL2 SDL2::IMAGE SDL2::TTF)
# add_test()