cmake_minimum_required(VERSION 3.15)

# Include catch.hpp file
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Unit tests for SDL2
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2)
