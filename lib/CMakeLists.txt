cmake_minimum_required(VERSION 3.15)

# SDL2
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2)

add_library(SDL2::SDL2 ALIAS SDL2)

macro(find_package)
    set(__find_package_list_var "${ARGV}")
    if (SDL2 IN_LIST __find_package_list_var)
        message("find_package trying to find sdl2!!!")
    else()
        message("calling find_package(${ARGV})")
        _find_package(${ARGV})
    endif()
endmacro()

# SDL2_image
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2_image)
add_library(SDL2::IMAGE ALIAS SDL2_image)

# SDL2_ttf
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2_ttf)
add_library(SDL2::TTF ALIAS SDL2_ttf)

# Catch2
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)

# EnTT
macro(add_subdirectory)
    set(__add_subdirectory_list_var "${ARGV}")
    if (test IN_LIST __add_subdirectory_list_var)
        message("add_subdirectory trying to add test dir!!!")
    else()
        message("calling find_package(${ARGV})")
        _add_subdirectory(${ARGV})
    endif()
endmacro()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/EnTT)

# spdlog
set(SPDLOG_BUILD_SHARED ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/spdlog)

# glm
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)
