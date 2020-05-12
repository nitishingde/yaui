cmake_minimum_required(VERSION 3.15)
project(yaui)

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

# 3rd party libraries: SDL2, SDL2_image, SDL2_ttf, Catch2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL2_ttf)

# Unit tests
add_subdirectory(${PROJECT_SOURCE_DIR}/unit_test)
