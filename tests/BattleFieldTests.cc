/*
 * File:        BattleFieldTests.cc
 * Description: Unit tests for BattleField class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        20.01.2025
 */

#define BOOST_TEST_MODULE FieldArmyTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>
#include "BattleField.h"
#include "UnitFactory.h"
#include "UnitType.h"

BOOST_AUTO_TEST_CASE(BattleField_constructor)
{
    FieldArmy player;
    FieldArmy enemy;
    HexMap<Tile> map(15, 11);
    std::fill(map.begin(), map.end(), Tile::REACHABLE);
    BattleField field(player, enemy, &map);
    BOOST_CHECK_EQUAL(0, field.getPlayer().getUnits().size());
    BOOST_CHECK_EQUAL(0, field.getEnemy().getUnits().size());
}

BOOST_AUTO_TEST_CASE(BattleField_constructor_units)
{
    FieldArmy player;
    FieldArmy enemy;
    player.addUnit(
        FieldUnit(
            Unit(UnitType::ARCHER, 2, 3, 4, 5, 6, 1, "", ""),
            Hex(8, 9)
    ));
    player.addUnit(
        FieldUnit(
            Unit(UnitType::ENCHANTER, 2, 3, 4, 5, 6, 3, "", ""),
            Hex(8, 9)
    ));
    enemy.addUnit(
        FieldUnit(
            Unit(UnitType::SKELETON, 2, 3, 4, 5, 6, 2, "", ""),
            Hex(8, 9)
    ));
    enemy.addUnit(
        FieldUnit(
            Unit(UnitType::SWORDSMAN, 2, 3, 4, 5, 6, 4, "", ""),
            Hex(8, 9)
    ));
    HexMap<Tile> map(15, 11);
    std::fill(map.begin(), map.end(), Tile::REACHABLE);

    BattleField field(player, enemy, &map);
    
    BOOST_CHECK_EQUAL(2, field.getPlayer().getUnits().size());
    BOOST_CHECK_EQUAL(2, field.getEnemy().getUnits().size());
    BOOST_CHECK_EQUAL(field.activeUnit().getUnitType(), UnitType::SWORDSMAN);
    BOOST_CHECK_EQUAL(field.getCurrentMoveType(), MoveType::MOVE);
    BOOST_CHECK_EQUAL(field.getQueue().current().type, ArmyType::COMPUTER);
}