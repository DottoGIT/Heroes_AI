#include "BattleManager.h"
#include "RendersVisitator.h"
#include "Logger.h"

BattleManager::BattleManager()
    : map_(BATTLE_HEX_WIDTH, BATTLE_HEX_HEIGHT)
{}

BattleManager::BattleManager(const FieldArmy &playerArmy, const FieldArmy &botArmy)
    : playerArmy_(playerArmy), botArmy_(botArmy), map_(BATTLE_HEX_WIDTH, BATTLE_HEX_HEIGHT)
{
    setInitiativeQueue();
    setUnitsInStartingPositions();

    background_ = "media/sprites/battlebg_green.png";
}

std::vector<std::shared_ptr<FieldUnit>> BattleManager::getAllUnits() const
{
    std::vector<std::shared_ptr<FieldUnit>> combinedVector;
    std::vector<std::shared_ptr<FieldUnit>> botUnits = botArmy_.getUnits();
    std::vector<std::shared_ptr<FieldUnit>> playerUnits = playerArmy_.getUnits();
    combinedVector.insert(combinedVector.end(), playerUnits.begin(), playerUnits.end());
    combinedVector.insert(combinedVector.end(), botUnits.begin(), botUnits.end());
    return combinedVector;
}

const std::string& BattleManager::getBackground() const
{
    return background_;
}

Hex BattleManager::getBattleGridDimensions() const
{
    return Hex(int(map_.getWidth()), int(map_.getHeight()));
}

void BattleManager::accept(RendersVisitator& visitor) const
{
    visitor.visitBattleManager(*this);
}

void BattleManager::setInitiativeQueue()
{
    std::vector<std::shared_ptr<FieldUnit>> combinedVector = getAllUnits();
    initiativeQueue_ = InitiativeQueue(combinedVector);
}

void BattleManager::setUnitsInStartingPositions()
{
    
}