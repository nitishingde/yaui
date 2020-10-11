cmake_minimum_required(VERSION 3.15)

project(yaui
    VERSION 1.0.0
    LANGUAGES CXX
)

# 3rd party libraries: SDL2, SDL2_image, SDL2_ttf, Catch2
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/SDL2_ttf)

# yaui library
add_library(yaui
    SHARED
        # entity
        src/entity/ViewFactory.cpp src/entity/ViewFactory.h

        # components
        src/component/BehaviourTraits.cpp src/component/BehaviourTraits.h
        src/component/BoxModel.cpp src/component/BoxModel.h
        src/component/Text.cpp src/component/Text.h
        src/component/Texture2D.cpp src/component/Texture2D.h
        src/component/Transform.cpp src/component/Transform.h

        # systems
        src/system/ISystem.cpp src/system/ISystem.h
        src/system/BehaviourSystem.cpp src/system/BehaviourSystem.h
        src/system/RenderingSystem.cpp src/system/RenderingSystem.h

        src/Behaviour.cpp src/Behaviour.h
        src/BehaviourFactory.cpp src/BehaviourFactory.h
        src/Director.cpp src/Director.h
        src/RendererWrapper.cpp src/RendererWrapper.h
        src/Scene.cpp src/Scene.h
        src/SystemJobScheduler.cpp src/SystemJobScheduler.h
        src/Types.h
        src/yaui.h
)

target_include_directories(yaui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(yaui
    PUBLIC
        SDL2::SDL2
        SDL2::IMAGE
        SDL2::TTF
        EnTT::EnTT
    INTERFACE
        Catch2::Catch2
)

add_library(yaui::yaui ALIAS yaui)

add_executable(qwerty unit_test/yaui/Test_yaui.cpp)
target_link_libraries(qwerty PRIVATE yaui::yaui)

# Unit tests
add_subdirectory(${PROJECT_SOURCE_DIR}/unit_test)

# Testing ground for libraries or anything temporary, it is ignored by vcs
add_subdirectory(${PROJECT_SOURCE_DIR}/experiment)

# Compile database (compile_commands.json) with compdb
execute_process(
    COMMAND compdb -p ${PROJECT_SOURCE_DIR}/build/ list
    OUTPUT_FILE ${PROJECT_SOURCE_DIR}/compile_commands.json
)
