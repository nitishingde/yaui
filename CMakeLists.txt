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
        src/entity/ViewBuilder.cpp src/entity/ViewBuilder.h
        src/entity/ViewFactory.cpp src/entity/ViewFactory.h

        # components
        src/component/Components.cpp src/component/Components.h

        # systems
        src/system/ISystem.cpp src/system/ISystem.h
        src/system/SystemJobScheduler.cpp src/system/SystemJobScheduler.h
        src/system/ActionSystem.cpp src/system/ActionSystem.h
        src/system/BehaviourSystem.cpp src/system/BehaviourSystem.h
        src/system/EventSystem.cpp src/system/EventSystem.h
        src/system/RenderingSystem.cpp src/system/RenderingSystem.h
        src/system/TextureTransformationSystem.cpp src/system/TextureTransformationSystem.h

        src/Action.cpp src/Action.h
        src/Behaviour.cpp src/Behaviour.h
        src/Director.cpp src/Director.h
        src/EventDispatcher.cpp src/EventDispatcher.h
        src/FocusEventHandler.cpp src/FocusEventHandler.h
        src/IEventHandler.cpp src/IEventHandler.h
        src/KeyboardEventHandler.cpp src/KeyboardEventHandler.h
        src/LoggerConstants.h
        src/MouseEventHandler.cpp src/MouseEventHandler.cpp
        src/RendererWrapper.cpp src/RendererWrapper.h
        src/Scene.cpp src/Scene.h
        src/TextInputEventHandler.cpp src/TextInputEventHandler.h
        src/TextureTransformation.cpp src/TextureTransformation.h
        src/TextureTransformationFactory.cpp src/TextureTransformationFactory.h
        src/Types.h
        src/Utility.cpp src/Utility.h
        src/WindowEventHandler.cpp src/WindowEventHandler.h
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
