cmake_minimum_required(VERSION 3.15)

add_executable(unit_test_yaui Test_yaui.cpp)
target_link_libraries(unit_test_yaui
    PRIVATE
        Catch2::Catch2
        spdlog::spdlog
        yaui::yaui
)

add_custom_target(CopyScript ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources
        ${CMAKE_CURRENT_BINARY_DIR}/
)

add_dependencies(unit_test_yaui CopyScript)