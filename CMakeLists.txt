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
        src/opengles2/Buffer.cpp src/opengles2/Buffer.h
        src/opengles2/Shader.cpp src/opengles2/Shader.h
        src/opengles2/Renderer.cpp src/opengles2/Renderer.h
        src/opengles2/Texture.cpp src/opengles2/Texture.h

        src/Director.cpp src/Director.h
        src/Types.h
        src/Utility.cpp src/Utility.h
)

target_include_directories(yaui
    PUBLIC
        # FIXME: remove the "opengles2/"
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(yaui
    PUBLIC
        OpenGL
        SDL2::SDL2
        glm::glm
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

