#include "BattleManager.h"
#include "RendersVisitator.h"
#include "Logger.h"

BattleManager::BattleManager()
{
    createHexMap();
    background_ = "Some background";
}

void BattleManager::setArmies(const FieldArmy& playerArmy, const FieldArmy& botArmy)
{
    playerArmy_ = playerArmy;
    botArmy_ = botArmy;

    setInitiativeQueue();
    setUnitsInStartingPositions();
}

std::vector<std::shared_ptr<FieldUnit>> BattleManager::getAllUnits() const
{
    std::vector<std::shared_ptr<FieldUnit>> combinedVector = playerArmy_.getUnits();
    combinedVector.insert(combinedVector.end(), botArmy_.getUnits().begin(), botArmy_.getUnits().end());
    return combinedVector;
}

const std::string& BattleManager::getBackground() const
{
    return background_;
}

void BattleManager::accept(RendersVisitator& visitor) const
{
    visitor.visitBattleManager(*this);
}

void BattleManager::createHexMap()
{
    map_ = std::make_unique<HexMap<std::shared_ptr<FieldUnit>>>(BATTLE_HEX_WIDTH, BATTLE_HEX_HEIGHT);
}

void BattleManager::setInitiativeQueue()
{
    std::vector<std::shared_ptr<FieldUnit>> combinedVector = getAllUnits();
    initiativeQueue_ = std::make_unique<InitiativeQueue>(combinedVector);
}


void BattleManager::setUnitsInStartingPositions()
{
    
}