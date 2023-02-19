cmake_minimum_required(VERSION 3.7...3.25)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Mini2DEngine VERSION 1.0
                     DESCRIPTION "Basic 2D game engine"
                     LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(RapidJSON REQUIRED)
include_directories(${RapidJSON_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_library(mini2dengine STATIC src/M2DMouseIO.cpp
                                src/M2DKeyboardIO.cpp
                                src/M2DUtilities.cpp
                                src/M2DText.cpp
                                src/M2DTextManager.cpp
                                )

target_link_libraries(mini2dengine ${SDL2_LIBRARIES})
target_link_libraries(mini2dengine ${SDL2_TTF_LIBRARIES})

target_include_directories(mini2dengine PRIVATE src/headers)
target_include_directories(mini2dengine PUBLIC include)