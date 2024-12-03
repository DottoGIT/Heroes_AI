# File:         CMakeLists.txt
# Description:  CMake build file for Heroes_AI project
# 
# Author:       Maciej Scheffer
# Date:         01.11.2024

cmake_minimum_required(VERSION 3.10)
project(Heroes_AI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost 1.86 REQUIRED COMPONENTS unit_test_framework)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(src src/headers src/enums)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB SOURCES src/source/*.cc)
file(GLOB HEADERS src/headers/*.h src/headers/*.hpp src/enums/*.h)

add_library(Heroes_AI_lib ${SOURCES} ${HEADERS})

add_executable(Heroes_AI src/main.cc)
target_link_libraries(Heroes_AI PRIVATE Heroes_AI_lib SDL2::SDL2 SDL2::SDL2main)

add_executable(UnitTests tests/UnitTests.cc)
target_link_libraries(Heroes_AI PRIVATE Heroes_AI_lib SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)
target_link_libraries(UnitTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES} SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)


enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)
