cmake_minimum_required(VERSION 3.15)

add_executable(unit_test_yaui Test_yaui.cpp)
target_link_libraries(unit_test_yaui
    PRIVATE
        Catch2::Catch2
        yaui::yaui
)

add_custom_command(
    TARGET unit_test_yaui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/
    $<TARGET_FILE_DIR:unit_test_yaui>/resources
)
