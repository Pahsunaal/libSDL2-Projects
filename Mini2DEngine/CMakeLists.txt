cmake_minimum_required(VERSION 3.7...3.25)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Mini2DEngine VERSION 1.0
                     DESCRIPTION "Basic 2D game engine"
                     LANGUAGES CXX)

add_library(mini2dengine STATIC src/GameObjects.cpp
                                src/GameRooms.cpp
                                src/GameSprites.cpp
                                src/GameText.cpp
                                src/InputHandlers.cpp
                                src/Source.cpp
                                src/Utilities.cpp
                                )

target_include_directories(mini2dengine PUBLIC include)