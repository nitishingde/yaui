cmake_minimum_required(VERSION 3.15)

project(stb
    VERSION 1.0.0
    LANGUAGES CXX
)

add_library(stb
    SHARED
        src/yaui_stb.h
        src/yaui_stb.cpp
        stb/stb_image.h
        stb/stb_truetype.h
)

target_include_directories(stb
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_library(yaui::stb ALIAS stb)
