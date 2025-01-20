/*
 * File:        FieldUnitTests.cc
 * Description: Unit tests for FieldUnit class
 *
 * Authors:     Wojciech Sarwiński
 * 
 * Date:        27.12.2024
 */

#define BOOST_TEST_MODULE FieldUnitTests
#include <boost/test/included/unit_test.hpp>
#include <algorithm>

#include "FieldUnit.h"
#include "UnitType.h"

BOOST_AUTO_TEST_CASE(FieldUnit_Constructor)
{
    Unit my_unit(UnitType::ARCHER, 2, 3, 4, 5, 6, 7, "", "");
    FieldUnit my_fieldUnit(my_unit, Hex(8, 9));

    BOOST_CHECK_EQUAL(UnitType::ARCHER, my_fieldUnit.getUnitType());
    BOOST_CHECK_EQUAL(Hex(8, 9), my_fieldUnit.getPosition());
    BOOST_CHECK_EQUAL(6, my_fieldUnit.getHealth().get());
    BOOST_CHECK_EQUAL(4, my_fieldUnit.getAttackStrength().get());
    BOOST_CHECK_EQUAL(5, my_fieldUnit.getAttackRange().get());
    BOOST_CHECK_EQUAL(6, my_fieldUnit.getWalkRange().get());
    BOOST_CHECK_EQUAL(7, my_fieldUnit.getInitiative().get());
}

BOOST_AUTO_TEST_CASE(FieldUnit_setPosition)
{
    Unit my_unit(UnitType::ARCHER, 2, 3, 4, 5, 6, 7, "", "");
    FieldUnit my_fieldUnit(my_unit, Hex(8, 9));

    my_fieldUnit.setPosition(Hex(3, 4));

    BOOST_CHECK_EQUAL(Hex(3, 4), my_fieldUnit.getPosition());
}

BOOST_AUTO_TEST_CASE(FieldUnit_damage)
{
    Unit my_unit(UnitType::ARCHER, 2, 5, 4, 5, 6, 7, "", "");
    FieldUnit my_fieldUnit(my_unit, Hex(8, 9));

    my_fieldUnit.takeDamage(3);

    BOOST_CHECK_EQUAL(7, my_fieldUnit.getHealth().get());
}

BOOST_AUTO_TEST_CASE(FieldUnit_lethal_damage)
{
    Unit my_unit(UnitType::ARCHER, 2, 5, 4, 5, 6, 7, "", "");
    FieldUnit my_fieldUnit(my_unit, Hex(8, 9));

    my_fieldUnit.takeDamage(15);

    BOOST_CHECK_EQUAL(0, my_fieldUnit.getHealth().get());
}

BOOST_AUTO_TEST_CASE(FieldUnit_exact_damage)
{
    Unit my_unit(UnitType::ARCHER, 2, 5, 4, 5, 6, 7, "", "");
    FieldUnit my_fieldUnit(my_unit, Hex(8, 9));

    my_fieldUnit.takeDamage(10);

    BOOST_CHECK_EQUAL(0, my_fieldUnit.getHealth().get());
}
