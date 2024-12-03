#include "FieldUnitFactory.h"
#include "FieldUnit.h"
#include "UnitType.h"
#include "RangeStrategy.h"
#include "MeleeStrategy.h"

// Constructor to register unit creators
FieldUnitFactory::FieldUnitFactory() {
    registerUnit(UnitType::Archer, &FieldUnitFactory::createArcher);
    registerUnit(UnitType::Enchanter, &FieldUnitFactory::createEnchanter);
    registerUnit(UnitType::Skeleton, &FieldUnitFactory::createSkeleton);
    registerUnit(UnitType::Swordsman, &FieldUnitFactory::createSwordsman);
}

std::shared_ptr<FieldUnit> FieldUnitFactory::CreateUnit(const UnitType& type, unsigned int quantity) {
    auto it = unit_creators_.find(type);
    if (it != unit_creators_.end()) {
        return (this->*(it->second))(quantity);
    }
    return nullptr;
}

void FieldUnitFactory::registerUnit(UnitType type, UnitCreator creator) {
    unit_creators_[type] = creator;
}

// Unit creation functions
std::shared_ptr<FieldUnit> FieldUnitFactory::createArcher(unsigned int quantity) {
    const UnitType                  UNIT_TYPE               = UnitType::Archer;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/archer.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/archer_dead.png";
    const unsigned int              UNIT_HEALTH             = 50;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 10;
    const unsigned int              UNIT_WALK_RANGE         = 5;
    const unsigned int              UNIT_INITIATIVE         = 7;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<RangeStrategy>();

    return std::make_shared<FieldUnit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, QUANTITY, PATH_TO_SPRITE_DEAD, UNIT_HEALTH,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}

std::shared_ptr<FieldUnit> FieldUnitFactory::createEnchanter(unsigned int quantity) {
    const UnitType                  UNIT_TYPE               = UnitType::Enchanter;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/enchanter.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/enchanter_dead.png";
    const unsigned int              UNIT_HEALTH             = 80;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 20;
    const unsigned int              UNIT_WALK_RANGE         = 3;
    const unsigned int              UNIT_INITIATIVE         = 8;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<RangeStrategy>();

    return std::make_shared<FieldUnit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, QUANTITY, PATH_TO_SPRITE_DEAD, UNIT_HEALTH,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}

std::shared_ptr<FieldUnit> FieldUnitFactory::createSkeleton(unsigned int quantity) {
    const UnitType                  UNIT_TYPE               = UnitType::Skeleton;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/skeleton.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/skeleton_dead.png";
    const unsigned int              UNIT_HEALTH             = 10;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 5;
    const unsigned int              UNIT_WALK_RANGE         = 7;
    const unsigned int              UNIT_INITIATIVE         = 3;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<MeleeStrategy>();

    return std::make_shared<FieldUnit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, QUANTITY, PATH_TO_SPRITE_DEAD, UNIT_HEALTH,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}

std::shared_ptr<FieldUnit> FieldUnitFactory::createSwordsman(unsigned int quantity) {
    const UnitType                  UNIT_TYPE               = UnitType::Swordsman;
    const std::string               PATH_TO_SPRITE_IDLE     = "media/sprites/swordsman.png";
    const unsigned int              QUANTITY                = quantity;
    const std::string               PATH_TO_SPRITE_DEAD     = "path/to/swordsman_dead.png";
    const unsigned int              UNIT_HEALTH             = 50;
    const unsigned int              UNIT_ATTACK_STRENGTH    = 20;
    const unsigned int              UNIT_WALK_RANGE         = 4;
    const unsigned int              UNIT_INITIATIVE         = 5;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<MeleeStrategy>();

    return std::make_shared<FieldUnit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, QUANTITY, PATH_TO_SPRITE_DEAD, UNIT_HEALTH,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}
