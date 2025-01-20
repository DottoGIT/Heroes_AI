/*
 * File:        UnitClassTests.cc
 * Description: Unit tests for Unit class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        27.12.2024
 */

#define BOOST_TEST_MODULE UnitClassTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>
#include "Unit.h"
#include "UnitType.h"

BOOST_AUTO_TEST_CASE(Unit_Constructor)
{
    Unit my_unit(UnitType::ARCHER, 1, 2, 3, 4, 5, 6, "", "");
    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_unit.getType());
    BOOST_CHECK_EQUAL(1, my_unit.getQuantity().get());
    BOOST_CHECK_EQUAL(2, my_unit.getSingleUnitHealth().get());
    BOOST_CHECK_EQUAL(3, my_unit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(4, my_unit.getAttackRange().get());
    BOOST_CHECK_EQUAL(5, my_unit.getWalkRange().get());
    BOOST_CHECK_EQUAL(6, my_unit.getInitiative().get());
}

BOOST_AUTO_TEST_CASE(Unit_Increase_Quantity)
{
    Unit my_unit(UnitType::ARCHER, 1, 1, 1, 1, 1, 1, "", "");
    my_unit.increaseQuantity(2);
    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_unit.getType());
    BOOST_CHECK_EQUAL(3, my_unit.getQuantity().get());
    BOOST_CHECK_EQUAL(1, my_unit.getSingleUnitHealth().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getWalkRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getInitiative().get());
}

BOOST_AUTO_TEST_CASE(Unit_Increase_Health)
{
    Unit my_unit(UnitType::ARCHER, 1, 1, 1, 1, 1, 1, "", "");
    my_unit.increaseSingleUnitHealth(2);
    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_unit.getType());
    BOOST_CHECK_EQUAL(1, my_unit.getQuantity().get());
    BOOST_CHECK_EQUAL(3, my_unit.getSingleUnitHealth().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getWalkRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getInitiative().get());
}

BOOST_AUTO_TEST_CASE(Unit_Increase_Strength)
{
    Unit my_unit(UnitType::ARCHER, 1, 1, 1, 1, 1, 1, "", "");
    my_unit.increaseAttackStrength(2);
    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_unit.getType());
    BOOST_CHECK_EQUAL(1, my_unit.getQuantity().get());
    BOOST_CHECK_EQUAL(1, my_unit.getSingleUnitHealth().get());
    BOOST_CHECK_EQUAL(3, my_unit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getWalkRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getInitiative().get());
}

BOOST_AUTO_TEST_CASE(Unit_Increase_Attack_Range)
{
    Unit my_unit(UnitType::ARCHER, 1, 1, 1, 1, 1, 1, "", "");
    my_unit.increaseAttackRange(2);
    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_unit.getType());
    BOOST_CHECK_EQUAL(1, my_unit.getQuantity().get());
    BOOST_CHECK_EQUAL(1, my_unit.getSingleUnitHealth().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(3, my_unit.getAttackRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getWalkRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getInitiative().get());
}

BOOST_AUTO_TEST_CASE(Unit_Increase_Walk_Range)
{
    Unit my_unit(UnitType::ARCHER, 1, 1, 1, 1, 1, 1, "", "");
    my_unit.increaseWalkRange(2);
    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_unit.getType());
    BOOST_CHECK_EQUAL(1, my_unit.getQuantity().get());
    BOOST_CHECK_EQUAL(1, my_unit.getSingleUnitHealth().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackRange().get());
    BOOST_CHECK_EQUAL(3, my_unit.getWalkRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getInitiative().get());
}

BOOST_AUTO_TEST_CASE(Unit_Increase_Initiative)
{
    Unit my_unit(UnitType::ARCHER, 1, 1, 1, 1, 1, 1, "", "");
    my_unit.increaseInitiative(2);
    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_unit.getType());
    BOOST_CHECK_EQUAL(1, my_unit.getQuantity().get());
    BOOST_CHECK_EQUAL(1, my_unit.getSingleUnitHealth().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(1, my_unit.getAttackRange().get());
    BOOST_CHECK_EQUAL(1, my_unit.getWalkRange().get());
    BOOST_CHECK_EQUAL(3, my_unit.getInitiative().get());
}
