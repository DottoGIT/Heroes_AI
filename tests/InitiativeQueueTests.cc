/*
 * File:        InitiativeQueueTests.cc
 * Description: Unit tests for InitiativeQueue class
 *
 * Authors:     Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        27.12.2024
 */

#define BOOST_TEST_MODULE InitiativeQueueTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>

#include "InitiativeQueue.h"
#include "UnitType.h"

BOOST_AUTO_TEST_CASE(InitiativeQueue_constructor) 
{
    FieldArmy player;
    FieldArmy enemy;
    player.addUnit(
        FieldUnit(
            Unit(UnitType::Archer, 1, 1, 1, 1, 1, 2),
            Hex(8, 9)
    ));
    enemy.addUnit(
        FieldUnit(
            Unit(UnitType::Archer, 1, 1, 1, 1, 1, 3),
            Hex(8, 9)
    ));
    InitiativeQueue queue(player, enemy);
    BOOST_REQUIRE_EQUAL(2, queue.getQueue().size());
    BOOST_CHECK_EQUAL(ArmyType::Computer, queue.getQueue().at(0));
    BOOST_CHECK_EQUAL(ArmyType::Player, queue.getQueue().at(1));
}

BOOST_AUTO_TEST_CASE(InitiativeQueue_constructor_larger_size) 
{
    FieldArmy player;
    FieldArmy enemy;
    player.addUnit(
        FieldUnit(
            Unit(UnitType::Archer, 1, 1, 1, 1, 1, 3),
            Hex(8, 9)
    ));
    player.addUnit(
        FieldUnit(
            Unit(UnitType::Archer, 1, 1, 1, 1, 1, 5),
            Hex(8, 9)
    ));
    enemy.addUnit(
        FieldUnit(
            Unit(UnitType::Archer, 1, 1, 1, 1, 1, 2),
            Hex(8, 9)
    ));
        enemy.addUnit(
        FieldUnit(
            Unit(UnitType::Archer, 1, 1, 1, 1, 1, 6),
            Hex(8, 9)
    ));
    InitiativeQueue queue(player, enemy);
    BOOST_REQUIRE_EQUAL(4, queue.getQueue().size());
    BOOST_CHECK_EQUAL(ArmyType::Computer, queue.getQueue().at(0).type);
    BOOST_CHECK_EQUAL(1,                  queue.getQueue().at(0).index);
    BOOST_CHECK_EQUAL(ArmyType::Player,   queue.getQueue().at(1).type);
    BOOST_CHECK_EQUAL(1,                  queue.getQueue().at(1).index);
    BOOST_CHECK_EQUAL(ArmyType::Player,   queue.getQueue().at(2).type);
    BOOST_CHECK_EQUAL(0,                  queue.getQueue().at(2).index);
    BOOST_CHECK_EQUAL(ArmyType::Computer, queue.getQueue().at(3).type);
    BOOST_CHECK_EQUAL(0,                  queue.getQueue().at(3).index);
}
