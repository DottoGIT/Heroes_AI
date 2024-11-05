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

#include "FieldUnit.h"
#include "RangeStrategy.h"
#include "FieldUnitFactory.h"
#include "FieldArmy.h"
#include "AttackType.h"
#include "UnitType.h"
#include "ArmyType.h"
#include "HexMap.hpp"
#include "BattleManager.h"
#include "InitiativeQueue.h"

BOOST_AUTO_TEST_SUITE(Units_Tests)

//////////////////////////////////////////////////
/*                    Unit                      */
//////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(Unit_Constructor_Tests)
{
    const UnitType TEST_TYPE = UnitType::Archer;
    const std::string TEST_IDLE_SPRITE = "sprites/archer_idle.png";
    const unsigned int TEST_QUANTITY = 10;

    Unit unit(TEST_TYPE, TEST_IDLE_SPRITE, TEST_QUANTITY);

    BOOST_CHECK_EQUAL(unit.getType(), TEST_TYPE);
    BOOST_CHECK_EQUAL(unit.getPathToSpriteIdle(), TEST_IDLE_SPRITE);
    BOOST_CHECK_EQUAL(unit.getQuantity(), TEST_QUANTITY);
}

//////////////////////////////////////////////////
/*                  FieldUnit                   */
//////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(FieldUnit_Constructor_Tests)
{
    const std::string TEST_IDLE_SPRITE = "sprites/archer_idle.png";
    const std::string TEST_DEAD_SPRITE = "sprites/archer_dead.png";
    const unsigned int TEST_QUANTITY = 20;
    const unsigned int TEST_SINGLE_UNIT_HEALTH = 10;
    const unsigned int TEST_ATTACK = 15;
    const unsigned int TEST_WALK_RANGE = 5;
    const unsigned int TEST_INITIATIVE = 8;
    auto attack_strategy = std::make_unique<RangeStrategy>();

    FieldUnit archer(
        UnitType::Archer, TEST_IDLE_SPRITE, TEST_QUANTITY, 
        TEST_DEAD_SPRITE, TEST_SINGLE_UNIT_HEALTH, TEST_ATTACK, 
        TEST_WALK_RANGE, TEST_INITIATIVE, std::move(attack_strategy));

    archer.setArmy(ArmyType::Computer);
    archer.setPosition(Hex(5, 10));

    BOOST_CHECK_EQUAL(archer.getType(), UnitType::Archer);
    BOOST_CHECK_EQUAL(archer.getPathToSpriteIdle(), TEST_IDLE_SPRITE);
    BOOST_CHECK_EQUAL(archer.getPathToSpriteDead(), TEST_DEAD_SPRITE);
    BOOST_CHECK_EQUAL(archer.getSingleUnitHealth(), TEST_SINGLE_UNIT_HEALTH);
    BOOST_CHECK_EQUAL(archer.getQuantity(), TEST_QUANTITY);
    BOOST_CHECK_EQUAL(archer.getAttackStrength(), TEST_ATTACK);
    BOOST_CHECK_EQUAL(archer.getWalkRange(), TEST_WALK_RANGE);
    BOOST_CHECK_EQUAL(archer.getInitiative(), TEST_INITIATIVE);
    BOOST_CHECK_EQUAL(archer.getAttackType(), AttackType::Ranged);
    BOOST_CHECK_EQUAL(archer.getArmyType(), ArmyType::Computer);
    BOOST_CHECK_EQUAL(archer.getPosition(), Hex(5, 10));
}

BOOST_AUTO_TEST_CASE(FieldUnitFactory_Creation_Tests)
{
    FieldUnitFactory factory;
    auto archer = factory.CreateUnit(UnitType::Archer, 10);
    BOOST_CHECK(archer != nullptr);
    
    auto field_unit = dynamic_cast<FieldUnit*>(archer.get());
    BOOST_REQUIRE(field_unit);

    BOOST_CHECK_EQUAL(field_unit->getType(), UnitType::Archer);
    BOOST_CHECK_EQUAL(field_unit->getSingleUnitHealth(), 50);
    BOOST_CHECK_EQUAL(field_unit->getQuantity(), 10);
    BOOST_CHECK_EQUAL(field_unit->getAttackStrength(), 10);
    BOOST_CHECK_EQUAL(field_unit->getWalkRange(), 5);
    BOOST_CHECK_EQUAL(field_unit->getInitiative(), 7);
    BOOST_CHECK_EQUAL(field_unit->getAttackType(), AttackType::Ranged);
}

//////////////////////////////////////////////////
/*                  FieldArmy                   */
//////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(FieldArmy_Tests)
{
    const UnitType TEST_TYPE = UnitType::Archer;
    const std::string TEST_IDLE_SPRITE = "sprites/archer_idle.png";
    const unsigned int TEST_QUANTITY = 10;

    Unit unit(TEST_TYPE, TEST_IDLE_SPRITE, TEST_QUANTITY);

    BOOST_CHECK_EQUAL(unit.getType(), TEST_TYPE);
    BOOST_CHECK_EQUAL(unit.getPathToSpriteIdle(), TEST_IDLE_SPRITE);
    BOOST_CHECK_EQUAL(unit.getQuantity(), TEST_QUANTITY);
}

BOOST_AUTO_TEST_CASE(FieldArmy_Constructor_Test)
{
    ArmyType armyType = ArmyType::Player;
    FieldArmy army(armyType);
    
    BOOST_CHECK_EQUAL(army.getUnits().size(), 0);
}

BOOST_AUTO_TEST_CASE(FieldArmy_AddUnit_Test)
{
    FieldUnitFactory factory;
    auto archer = factory.CreateUnit(UnitType::Archer, 10);
    auto swordsman = factory.CreateUnit(UnitType::Swordsman, 10);
    auto archer2 = factory.CreateUnit(UnitType::Swordsman, 33);
    ArmyType armyType = ArmyType::Computer;
    FieldArmy army(armyType);
    
    army.addUnit(archer);
    army.addUnit(swordsman);
    army.addUnit(archer2);
    
    const auto& units = army.getUnits();
    BOOST_CHECK_EQUAL(units.size(), 3);
    BOOST_CHECK(units[0] == archer);
    BOOST_CHECK(units[1] == swordsman);
    BOOST_CHECK(units[2] == archer2);
}

//////////////////////////////////////////////////
/*              InitiativeQueue                 */
//////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(InitiativeQueue_popNextAndPush_Test) 
{
    FieldUnitFactory factory;
    
    auto archer = factory.CreateUnit(UnitType::Archer);
    auto skeleton = factory.CreateUnit(UnitType::Skeleton);
    auto swordsman = factory.CreateUnit(UnitType::Swordsman);
    auto enchanter = factory.CreateUnit(UnitType::Enchanter);
    std::vector<std::shared_ptr<FieldUnit>> units = {
        archer,     // 7
        enchanter,  // 8
        skeleton,   // 3 
        swordsman   // 5
    };
    
    InitiativeQueue queue(units);

    BOOST_CHECK(queue.popNextAndPush()->getType() == UnitType::Enchanter);
    BOOST_CHECK(queue.popNextAndPush()->getType() == UnitType::Archer);
    BOOST_CHECK(queue.popNextAndPush()->getType() == UnitType::Swordsman);
    BOOST_CHECK(queue.popNextAndPush()->getType() == UnitType::Skeleton);
    BOOST_CHECK(queue.popNextAndPush()->getType() == UnitType::Enchanter);
    BOOST_CHECK(queue.popNextAndPush()->getType() == UnitType::Archer);
}

BOOST_AUTO_TEST_CASE(InitiativeQueue_LookUpNextUnits_Test) 
{
    FieldUnitFactory factory;
    
    auto archer = factory.CreateUnit(UnitType::Archer);
    auto skeleton = factory.CreateUnit(UnitType::Skeleton);
    auto swordsman = factory.CreateUnit(UnitType::Swordsman);
    auto enchanter = factory.CreateUnit(UnitType::Enchanter);
    std::vector<std::shared_ptr<FieldUnit>> units = {
        archer,     // 7
        enchanter,  // 8
        skeleton,   // 3 
        swordsman   // 5
    };
    
    InitiativeQueue queue(units);
    std::vector<std::shared_ptr<FieldUnit>> lookUpResult = queue.lookUpNextUnits(6);

    BOOST_CHECK(lookUpResult[0]->getType() == UnitType::Enchanter);
    BOOST_CHECK(lookUpResult[1]->getType() == UnitType::Archer);
    BOOST_CHECK(lookUpResult[2]->getType() == UnitType::Swordsman);
    BOOST_CHECK(lookUpResult[3]->getType() == UnitType::Skeleton);
    BOOST_CHECK(lookUpResult[4]->getType() == UnitType::Enchanter);
    BOOST_CHECK(lookUpResult[5]->getType() == UnitType::Archer);
}

BOOST_AUTO_TEST_SUITE_END()
