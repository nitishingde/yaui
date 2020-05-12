cmake_minimum_required(VERSION 3.15)
project(yaui)

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

# 3rd party libraries: SDL2, SDL2_image, SDL2_ttf, Catch2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL2_ttf)

# yaui library
add_library(yaui
    src/Components/Component.cpp src/Components/Component.h

    src/Components/BoxModel/Transform.cpp src/Components/BoxModel/Transform.h
    src/Components/BoxModel/Padding.cpp src/Components/BoxModel/Padding.h
    src/Components/BoxModel/Border.cpp src/Components/BoxModel/Border.h
    src/Components/BoxModel/Margin.cpp src/Components/BoxModel/Margin.h

    src/Components/Layout/HorizontalLayout.cpp src/Components/Layout/HorizontalLayout.h
    src/Components/Layout/VerticalLayout.cpp src/Components/Layout/VerticalLayout.h

    src/Components/Renderer/Texture.cpp src/Components/Renderer/Texture.h
    src/Components/Renderer/Sprite.cpp src/Components/Renderer/Sprite.h
    src/Components/Renderer/Text.cpp src/Components/Renderer/Text.h
)

# yaui engine
add_executable(yaui_engine
    src/Entity/ViewObject.cpp src/Entity/ViewObject.h

    src/System/LayoutManager.cpp src/System/LayoutManager.h
    src/System/RenderingManager.cpp src/System/RenderingManager.h
    src/System/LayerManager.cpp src/System/LayerManager.h
    src/System/EventManager.cpp src/System/EventManager.h
)

include_directories(
    src/Entity

    src/Components
    src/Components/BoxModel
    src/Components/Layout
    src/Components/Renderer

    src/System
)

target_link_libraries(yaui
    SDL2::SDL2
    SDL2::IMAGE
    SDL2::TTF
)

target_link_libraries(yaui_engine
    SDL2::SDL2
    SDL2::IMAGE
    SDL2::TTF
    yaui
)

# Unit tests
add_subdirectory(${PROJECT_SOURCE_DIR}/unit_test)

# Testing ground for libraries or anything temporary, it is ignored by vcs
add_subdirectory(${PROJECT_SOURCE_DIR}/experiment)
