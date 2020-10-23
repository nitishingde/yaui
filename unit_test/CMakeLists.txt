cmake_minimum_required(VERSION 3.15)

# Unit tests for SDL2
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2)

# Unit tests for EnTT
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/EnTT)

# Unit tests for yaui
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/yaui)

# Unit test for spdlog
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/spdlog)

add_test(all_test
    unit_test_sdl2
    unit_test_entt
    unit_test_yaui
    unit_test_spdlog
)
