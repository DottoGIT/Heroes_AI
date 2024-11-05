#include "Unit.h"
#include "UnitFactory.h"
#include "UnitType.h"
#include "RangeStrategy.h"
#include "MeleeStrategy.h"

// Constructor to register unit creators
UnitFactory::UnitFactory() {
    registerUnit(UnitType::Archer, &UnitFactory::createArcher);
    registerUnit(UnitType::Enchanter, &UnitFactory::createEnchanter);
    registerUnit(UnitType::Skeleton, &UnitFactory::createSkeleton);
    registerUnit(UnitType::Swordsman, &UnitFactory::createSwordsman);
}

std::unique_ptr<Unit> UnitFactory::CreateUnit(const UnitType& type, unsigned int number_in_stack) {
    auto it = unit_creators_.find(type);
    if (it != unit_creators_.end()) {
        return (this->*(it->second))(number_in_stack);
    }
    return nullptr;
}

void UnitFactory::registerUnit(UnitType type, UnitCreator creator) {
    unit_creators_[type] = creator;
}

// Unit creation functions
std::unique_ptr<Unit> UnitFactory::createArcher(unsigned int number_in_stack) {
    UnitType                        UNIT_TYPE               = UnitType::Archer;
    std::string                     PATH_TO_SPRITE_IDLE     = "path/to/archer_idle.png";
    std::string                     PATH_TO_SPRITE_DEAD     = "path/to/archer_dead.png";
    unsigned int                    UNIT_HEALTH             = 50;
    unsigned int                    UNIT_ATTACK_STRENGTH    = 10;
    unsigned int                    UNIT_WALK_RANGE         = 5;
    unsigned int                    UNIT_INITIATIVE         = 7;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<RangeStrategy>();

    return std::make_unique<Unit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD, UNIT_HEALTH, UNIT_HEALTH * number_in_stack,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}

std::unique_ptr<Unit> UnitFactory::createEnchanter(unsigned int number_in_stack) {
    UnitType                        UNIT_TYPE               = UnitType::Enchanter;
    std::string                     PATH_TO_SPRITE_IDLE     = "path/to/enchanter_idle.png";
    std::string                     PATH_TO_SPRITE_DEAD     = "path/to/enchanter_dead.png";
    unsigned int                    UNIT_HEALTH             = 80;
    unsigned int                    UNIT_ATTACK_STRENGTH    = 20;
    unsigned int                    UNIT_WALK_RANGE         = 3;
    unsigned int                    UNIT_INITIATIVE         = 8;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<RangeStrategy>();

    return std::make_unique<Unit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD, UNIT_HEALTH, UNIT_HEALTH * number_in_stack,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}

std::unique_ptr<Unit> UnitFactory::createSkeleton(unsigned int number_in_stack) {
    UnitType                        UNIT_TYPE               = UnitType::Skeleton;
    std::string                     PATH_TO_SPRITE_IDLE     = "path/to/skeleton_idle.png";
    std::string                     PATH_TO_SPRITE_DEAD     = "path/to/skeleton_dead.png";
    unsigned int                    UNIT_HEALTH             = 10;
    unsigned int                    UNIT_ATTACK_STRENGTH    = 5;
    unsigned int                    UNIT_WALK_RANGE         = 7;
    unsigned int                    UNIT_INITIATIVE         = 3;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<MeleeStrategy>();

    return std::make_unique<Unit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD, UNIT_HEALTH, UNIT_HEALTH * number_in_stack,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}

std::unique_ptr<Unit> UnitFactory::createSwordsman(unsigned int number_in_stack) {
    UnitType                        UNIT_TYPE               = UnitType::Swordsman;
    std::string                     PATH_TO_SPRITE_IDLE     = "path/to/swordsman_idle.png";
    std::string                     PATH_TO_SPRITE_DEAD     = "path/to/swordsman_dead.png";
    unsigned int                    UNIT_HEALTH             = 50;
    unsigned int                    UNIT_ATTACK_STRENGTH    = 20;
    unsigned int                    UNIT_WALK_RANGE         = 4;
    unsigned int                    UNIT_INITIATIVE         = 5;
    std::unique_ptr<AttackStrategy> UNIT_ATTACK_STRATEGY    = std::make_unique<MeleeStrategy>();

    return std::make_unique<Unit>(UNIT_TYPE, PATH_TO_SPRITE_IDLE, PATH_TO_SPRITE_DEAD, UNIT_HEALTH, UNIT_HEALTH * number_in_stack,
                                  UNIT_ATTACK_STRENGTH, UNIT_WALK_RANGE, UNIT_INITIATIVE, std::move(UNIT_ATTACK_STRATEGY));
}
