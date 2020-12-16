cmake_minimum_required(VERSION 3.15)

add_executable(unit_test_yaml Test_yaml.cpp)
target_link_libraries(unit_test_yaml
    PRIVATE
        yaml-cpp
        Catch2::Catch2
)

add_custom_command(
        TARGET unit_test_yaml POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/test.yaml
        $<TARGET_FILE_DIR:unit_test_yaml>/test.yaml
)
