/*
 * File:        FieldArmyTests.cc
 * Description: Unit tests for FieldArmy class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        27.12.2024
 */

#define BOOST_TEST_MODULE FieldArmyTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>
#include "FieldArmy.h"
#include "UnitType.h"

BOOST_AUTO_TEST_CASE(FieldArmy_Constructor)
{
    FieldArmy army;
    BOOST_CHECK_EQUAL(0, army.getUnits().size());
}

BOOST_AUTO_TEST_CASE(FieldArmy_addUnit)
{
    FieldArmy army;
    army.addUnit(
        FieldUnit(
            Unit(UnitType::ARCHER, 2, 3, 4, 5, 6, 7, "", ""),
            Hex(8, 9)
    ));
    
    BOOST_REQUIRE_EQUAL(1, army.getUnits().size());
    BOOST_CHECK_EQUAL(UnitType::ARCHER, army.at(0).getUnitType());
}

BOOST_AUTO_TEST_CASE(FieldArmy_citerator)
{
    FieldArmy army;
    army.addUnit(
        FieldUnit(
            Unit(UnitType::ARCHER, 2, 3, 4, 5, 6, 7, "", ""),
            Hex(8, 9)
    ));

    BOOST_REQUIRE_EQUAL(1, army.getUnits().size());
    auto it = army.cbegin();
    BOOST_REQUIRE(it != army.cend());
    BOOST_CHECK_EQUAL(UnitType::ARCHER, it->getUnitType());
    ++it;
    BOOST_CHECK(it == army.cend());
}