cmake_minimum_required(VERSION 3.15)

project(yaui
    VERSION 1.0.0
    LANGUAGES CXX
)

# 3rd party libraries: SDL2, SDL2_image, SDL2_ttf, Catch2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL2_ttf)

# yaui library
add_library(yaui
    SHARED
        src/yaui.h
        src/Types.h
)

target_include_directories(yaui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(yaui
    PUBLIC
        SDL2::SDL2
        SDL2::IMAGE
        SDL2::TTF
        EnTT::EnTT
)

add_library(yaui::yaui ALIAS yaui)

add_executable(qwerty unit_test/yaui/Test_yaui.cpp)
target_link_libraries(qwerty PRIVATE yaui::yaui)

# Unit tests
add_subdirectory(${PROJECT_SOURCE_DIR}/unit_test)

# Testing ground for libraries or anything temporary, it is ignored by vcs
add_subdirectory(${PROJECT_SOURCE_DIR}/experiment)

# Compile database (compile_commands.json) with compdb
execute_process(
    COMMAND compdb -p ${PROJECT_SOURCE_DIR}/build/ list
    OUTPUT_FILE ${PROJECT_SOURCE_DIR}/compile_commands.json
)
