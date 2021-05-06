cmake_minimum_required(VERSION 3.15)

project(yaui
    VERSION 1.0.0
    LANGUAGES CXX
)

# 3rd party libraries: SDL2, SDL2_image, SDL2_ttf, Catch2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL2_ttf)

find_package(OpenGL REQUIRED)

# yaui library
add_library(yaui
    SHARED
        # OpenGL ES 2
        src/gles2/Buffer.cpp src/gles2/Buffer.h
        src/gles2/Shader.cpp src/gles2/Shader.h
        src/gles2/Renderer.cpp src/gles2/Renderer.h
        src/gles2/Texture.cpp src/gles2/Texture.h
        src/gles2/Window.cpp src/gles2/Window.h

        # Component
        src/component/Component.cpp src/component/Component.h

        # System
        src/system/System.cpp src/system/System.h
        src/system/SystemJobScheduler.cpp src/system/SystemJobScheduler.h

        src/Director.cpp src/Director.h
        src/Scene.cpp src/Scene.h
        src/Types.h
        src/Utility.cpp src/Utility.h
)

target_include_directories(yaui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(yaui
    PUBLIC
        EnTT::EnTT
        glm::glm
        OpenGL
        SDL2::SDL2
        yaui::stb
    PRIVATE
        spdlog::spdlog
    INTERFACE
        Catch2::Catch2
)

add_library(yaui::yaui ALIAS yaui)

# Unit tests
add_subdirectory(${PROJECT_SOURCE_DIR}/unit_test)

# Testing ground for libraries or anything temporary, it is ignored by vcs
add_subdirectory(${PROJECT_SOURCE_DIR}/experiment)

# Compile database (compile_commands.json) with compdb
execute_process(
    COMMAND compdb -p ${PROJECT_SOURCE_DIR}/build/ list
    OUTPUT_FILE ${PROJECT_SOURCE_DIR}/compile_commands.json
)

