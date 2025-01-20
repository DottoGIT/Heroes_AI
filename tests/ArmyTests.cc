/*
 * File:        ArmyTests.cc
 * Description: Unit tests for Army class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        19.01.2025
 */

#define BOOST_TEST_MODULE FieldArmyTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>
#include "Army.h"
#include "UnitType.h"

BOOST_AUTO_TEST_CASE(FieldArmy_Constructor)
{
    Army army;
    BOOST_CHECK_EQUAL(0, army.getUnits().size());
}

BOOST_AUTO_TEST_CASE(FieldArmy_addUnit)
{
    Army army;
    army.addUnit(Unit(UnitType::ARCHER, 2, 3, 4, 5, 6, 7, "", ""));
    
    BOOST_REQUIRE_EQUAL(1, army.getUnits().size());
    BOOST_CHECK_EQUAL(UnitType::ARCHER, army.getUnits().at(0).getType());
}

BOOST_AUTO_TEST_CASE(FieldArmy_citerator)
{
    Army army;
    army.addUnit(Unit(UnitType::ARCHER, 2, 3, 4, 5, 6, 7, "", ""));
    army.addUnit(Unit(UnitType::ENCHANTER, 3, 4, 5, 6, 7, 8, "", ""));
    
    BOOST_REQUIRE_EQUAL(2, army.getUnits().size());

    auto it = army.cbegin();
    BOOST_REQUIRE(it != army.cend());
    BOOST_CHECK_EQUAL(UnitType::ARCHER, it->getType());
    ++it;
    BOOST_REQUIRE(it != army.cend());
    BOOST_CHECK_EQUAL(UnitType::ENCHANTER, it->getType());
    ++it;
    BOOST_CHECK(it == army.cend());
}