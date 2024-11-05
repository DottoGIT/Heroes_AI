/*
 * File:        UnitTests.cc
 * Description: Unit tests for Heroes_AI project
 *
 * Authors:     Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwiński
 * 
 * Date:        01.11.2024
 */

#define BOOST_TEST_MODULE UnitTests
#include <boost/test/included/unit_test.hpp>

#include "Unit.h"
#include "RangeStrategy.h"
#include "UnitFactory.h"
#include "AttackType.h"
#include "UnitType.h"

BOOST_AUTO_TEST_SUITE(Units_Tests)

BOOST_AUTO_TEST_CASE(Unit_Constructor_Tests)
{
    const std::string TEST_NAME = "Archer";
    const std::string TEST_IDLE_SPRITE = "sprites/archer_idle.png";
    const std::string TEST_DEAD_SPRITE = "sprites/archer_dead.png";
    const unsigned int TEST_SINGLE_UNIT_HEALTH = 10;
    const unsigned int TEST_STACK_HEALTH = 100;
    const unsigned int TEST_ATTACK = 15;
    const unsigned int TEST_WALK_RANGE = 5;
    const unsigned int TEST_INITIATIVE = 8;
    auto attack_strategy = std::make_unique<RangeStrategy>();

    Unit archer(UnitType::Archer, TEST_IDLE_SPRITE, TEST_DEAD_SPRITE, 
                 TEST_SINGLE_UNIT_HEALTH, TEST_STACK_HEALTH, 
                 TEST_ATTACK, TEST_WALK_RANGE, TEST_INITIATIVE, 
                 std::move(attack_strategy));
    

    BOOST_CHECK_EQUAL(archer.getType(), UnitType::Archer);
    BOOST_CHECK_EQUAL(archer.getPathToSpriteIdle(), TEST_IDLE_SPRITE);
    BOOST_CHECK_EQUAL(archer.getPathToSpriteDead(), TEST_DEAD_SPRITE);
    BOOST_CHECK_EQUAL(archer.getSingleUnitHealth(), TEST_SINGLE_UNIT_HEALTH);
    BOOST_CHECK_EQUAL(archer.getStackHealth(), TEST_STACK_HEALTH);
    BOOST_CHECK_EQUAL(archer.getAttackStrength(), TEST_ATTACK);
    BOOST_CHECK_EQUAL(archer.getWalkRange(), TEST_WALK_RANGE);
    BOOST_CHECK_EQUAL(archer.getInitiative(), TEST_INITIATIVE);
    BOOST_CHECK_EQUAL(archer.getAttackType(), AttackType::Ranged);
}

BOOST_AUTO_TEST_CASE(UnitFactory_Creation_Tests)
{
    UnitFactory factory;
    auto archer = factory.CreateUnit(UnitType::Archer, 10);
    BOOST_CHECK(archer != nullptr);
    BOOST_CHECK_EQUAL(archer->getType(), UnitType::Archer);
    BOOST_CHECK_EQUAL(archer->getSingleUnitHealth(), 50);
    BOOST_CHECK_EQUAL(archer->getStackHealth(), 500);
    BOOST_CHECK_EQUAL(archer->getAttackStrength(), 10);
    BOOST_CHECK_EQUAL(archer->getWalkRange(), 5);
    BOOST_CHECK_EQUAL(archer->getInitiative(), 7);
    BOOST_CHECK_EQUAL(archer->getAttackType(), AttackType::Ranged);
}
BOOST_AUTO_TEST_SUITE_END()
