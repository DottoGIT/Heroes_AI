#include <stdexcept>
#include "UnitFactory.h"
#include "Unit.h"
#include "FieldUnit.h"
#include "UnitType.h"
#include "RangeStrategy.h"
#include "MeleeStrategy.h"



// Constructor to register unit creators


UnitFactory::UnitFactory()
{
    registerUnit(UnitType::Archer, &UnitFactory::createArcher);
    registerUnit(UnitType::Enchanter, &UnitFactory::createEnchanter);
    registerUnit(UnitType::Skeleton, &UnitFactory::createSkeleton);
    registerUnit(UnitType::Swordsman, &UnitFactory::createSwordsman);
}

void UnitFactory::registerUnit(UnitType type, UnitCreator creator)
{
    unit_creators_[type] = creator;
}

Unit UnitFactory::CreateUnit(const UnitType& type, unsigned int quantity) {
    auto it = unit_creators_.find(type);
    if (it == unit_creators_.end()) 
        throw std::out_of_range("Unit type not registered.");
    return (this->*(it->second))(quantity);
}

Unit UnitFactory::createArcher(unsigned int quantity)
{
    const UnitType                  UNIT_TYPE               = UnitType::Archer;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/archer.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/archer_dead.png";
    const unsigned int              UNIT_HEALTH             = 50;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 10;
    const unsigned int              UNIT_ATTACK_RANGE       = 5;
    const unsigned int              UNIT_WALK_RANGE         = 5;
    const unsigned int              UNIT_INITIATIVE         = 7;

    return Unit(UNIT_TYPE, quantity, UNIT_HEALTH, UNIT_ATTACK_STRENGTH, UNIT_ATTACK_RANGE, UNIT_WALK_RANGE, UNIT_INITIATIVE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD);
}

Unit UnitFactory::createEnchanter(unsigned int quantity)
{
    const UnitType                  UNIT_TYPE               = UnitType::Enchanter;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/enchanter.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/enchanter_dead.png";
    const unsigned int              UNIT_HEALTH             = 80;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 20;
    const unsigned int              UNIT_ATTACK_RANGE       = 5;
    const unsigned int              UNIT_WALK_RANGE         = 3;
    const unsigned int              UNIT_INITIATIVE         = 8;

    return Unit(UNIT_TYPE, quantity, UNIT_HEALTH, UNIT_ATTACK_STRENGTH, UNIT_ATTACK_RANGE, UNIT_WALK_RANGE, UNIT_INITIATIVE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD);
}

Unit UnitFactory::createSkeleton(unsigned int quantity)
{
    const UnitType                  UNIT_TYPE               = UnitType::Skeleton;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/skeleton.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/skeleton_dead.png";
    const unsigned int              UNIT_HEALTH             = 10;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 5;
    const unsigned int              UNIT_ATTACK_RANGE       = 1;
    const unsigned int              UNIT_WALK_RANGE         = 7;
    const unsigned int              UNIT_INITIATIVE         = 3;

    return Unit(UNIT_TYPE, quantity, UNIT_HEALTH, UNIT_ATTACK_STRENGTH, UNIT_ATTACK_RANGE, UNIT_WALK_RANGE, UNIT_INITIATIVE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD);
}

Unit UnitFactory::createSwordsman(unsigned int quantity)
{
    const UnitType                  UNIT_TYPE               = UnitType::Swordsman;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/swordsman.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/swordsman_dead.png";
    const unsigned int              UNIT_HEALTH             = 50;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 20;
    const unsigned int              UNIT_ATTACK_RANGE       = 1;
    const unsigned int              UNIT_WALK_RANGE         = 4;
    const unsigned int              UNIT_INITIATIVE         = 5;

    return Unit(UNIT_TYPE, quantity, UNIT_HEALTH, UNIT_ATTACK_STRENGTH, UNIT_ATTACK_RANGE, UNIT_WALK_RANGE, UNIT_INITIATIVE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD);
}