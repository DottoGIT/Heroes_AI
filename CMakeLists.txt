# File:         CMakeLists.txt
# Description:  CMake build file for Heroes_AI project
# 
# Author:       Maciej Scheffer
# Date:         01.11.2024

cmake_minimum_required(VERSION 3.10)
project(Heroes_AI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost 1.83 REQUIRED COMPONENTS unit_test_framework)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(src src/headers src/enums)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB SOURCES src/source/*.cc)
file(GLOB HEADERS src/headers/*.h src/headers/*.hpp src/enums/*.h)

add_library(Heroes_AI_lib ${SOURCES} ${HEADERS})

add_executable(Heroes_AI src/main.cc)

target_link_libraries(Heroes_AI PRIVATE Heroes_AI_lib SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

add_executable(UnitTests tests/UnitTests.cc)
target_link_libraries(UnitTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES} SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

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

add_executable(ArmyTests tests/ArmyTests.cc)
target_link_libraries(ArmyTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})

add_executable(BattleFieldTests tests/BattleFieldTests.cc)
target_link_libraries(BattleFieldTests PRIVATE Heroes_AI_lib ${Boost_LIBRARIES})



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
add_test(NAME ArmyTests COMMAND ArmyTests)
add_test(NAME BattleFieldTests COMMAND BattleFieldTests)
