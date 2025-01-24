# File:         CMakeLists.txt
# Description:  CMake build file for Heroes_AI project with SDL2_image and SDL2_ttf handling
# 
# Author:       Maciej Scheffer
# Date:         01.11.2024

cmake_minimum_required(VERSION 3.10)
project(Heroes_AI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /path/to/your/modules)

# Find Boost
find_package(Boost 1.74 REQUIRED COMPONENTS unit_test_framework)

# Find SDL2
find_package(SDL2 REQUIRED)

# Find SDL2_image
find_package(SDL2_image QUIET)
if (NOT SDL2_image_FOUND)
    message(WARNING "SDL2_image not found via find_package, using pkg-config as fallback")
    find_program(PKG_CONFIG pkg-config)
    if (PKG_CONFIG)
        execute_process(COMMAND ${PKG_CONFIG} --cflags-only-I SDL2_image
                        OUTPUT_VARIABLE SDL2_IMAGE_INCLUDE_DIRS
                        OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(COMMAND ${PKG_CONFIG} --libs SDL2_image
                        OUTPUT_VARIABLE SDL2_IMAGE_LIBRARIES
                        OUTPUT_STRIP_TRAILING_WHITESPACE)
        if (NOT SDL2_IMAGE_INCLUDE_DIRS OR NOT SDL2_IMAGE_LIBRARIES)
            message(FATAL_ERROR "SDL2_image not found via pkg-config either!")
        endif ()
        message(STATUS "SDL2_image found using pkg-config")
    else ()
        message(FATAL_ERROR "pkg-config not found!")
    endif ()
endif ()

# Find SDL2_ttf
find_package(SDL2_ttf QUIET)
if (NOT SDL2_ttf_FOUND)
    message(WARNING "SDL2_ttf not found via find_package, using pkg-config as fallback")
    find_program(PKG_CONFIG pkg-config)
    if (PKG_CONFIG)
        execute_process(COMMAND ${PKG_CONFIG} --cflags-only-I SDL2_ttf
                        OUTPUT_VARIABLE SDL2_TTF_INCLUDE_DIRS
                        OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(COMMAND ${PKG_CONFIG} --libs SDL2_ttf
                        OUTPUT_VARIABLE SDL2_TTF_LIBRARIES
                        OUTPUT_STRIP_TRAILING_WHITESPACE)
        if (NOT SDL2_TTF_INCLUDE_DIRS OR NOT SDL2_TTF_LIBRARIES)
            message(FATAL_ERROR "SDL2_ttf not found via pkg-config either!")
        endif ()
        message(STATUS "SDL2_ttf found using pkg-config")
    else ()
        message(FATAL_ERROR "pkg-config not found!")
    endif ()
endif ()

# Include directories
include_directories(src src/headers src/enums)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# Source files
file(GLOB SOURCES src/source/*.cc)
file(GLOB HEADERS src/headers/*.h src/headers/*.hpp src/enums/*.h)

# Library
add_library(Heroes_AI_lib ${SOURCES} ${HEADERS})

# Main executable
add_executable(Heroes_AI src/main.cc)
target_link_libraries(Heroes_AI PRIVATE Heroes_AI_lib SDL2::SDL2 SDL2::SDL2main ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Tests
add_executable(UnitTests tests/UnitTests.cc)
target_link_libraries(UnitTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES} SDL2::SDL2 SDL2::SDL2main ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

add_executable(HexTests tests/HexTests.cc)
target_link_libraries(HexTests Boost::unit_test_framework)
target_sources(HexTests PRIVATE src/source/Hex.cc)

add_executable(HexMapTests tests/HexMapTests.cc)
target_link_libraries(HexMapTests Boost::unit_test_framework)
target_sources(HexMapTests PRIVATE src/source/Hex.cc src/headers/HexMap.hpp)

add_executable(HealthTests tests/HealthTests.cc)
target_link_libraries(HealthTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})

add_executable(StatisticTests tests/StatisticTests.cc)
target_link_libraries(StatisticTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})

add_executable(UnitClassTests tests/UnitClassTests.cc)
target_link_libraries(UnitClassTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})

add_executable(FieldUnitTests tests/FieldUnitTests.cc)
target_link_libraries(FieldUnitTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})

add_executable(FieldArmyTests tests/FieldArmyTests.cc)
target_link_libraries(FieldArmyTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})

add_executable(InitiativeQueueTests tests/InitiativeQueueTests.cc)
target_link_libraries(InitiativeQueueTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})

# Enable tests
enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)
add_test(NAME HexTests COMMAND HexTests)
add_test(NAME HexMapTests COMMAND HexMapTests)
add_test(NAME HealthTests COMMAND HealthTests)
add_test(NAME StatisticTests COMMAND StatisticTests)
add_test(NAME UnitClassTests COMMAND UnitClassTests)
add_test(NAME FieldUnitTests COMMAND FieldUnitTests)
add_test(NAME FieldArmyTests COMMAND FieldArmyTests)
add_test(NAME InitiativeQueueTests COMMAND InitiativeQueueTests)