cmake_minimum_required(VERSION 3.15)

add_executable(unit_test_spdlog Test_spdlog.cpp)
target_link_libraries(unit_test_spdlog
    PRIVATE
        spdlog::spdlog
        Catch2::Catch2
)
