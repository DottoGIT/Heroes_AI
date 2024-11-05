#include "BattleManager.h"
#include "FieldArmy.h"
#include "InitiativeQueue.h"
#include "HexMap.hpp"
#include "FieldUnit.h"

BattleManager::BattleManager(FieldArmy& playerArmy, FieldArmy& botArmy)
    : playerArmy_(playerArmy), botArmy_(botArmy)
{
    createHexMap();
    setInitiativeQueue();
    setUnitsInStartingPositions();
}

void BattleManager::createHexMap()
{
    map_ = std::make_unique<HexMap<std::shared_ptr<FieldUnit>>>(BATTLE_HEX_WIDTH, BATTLE_HEX_HEIGHT);
}

void BattleManager::setInitiativeQueue()
{
    std::vector<std::shared_ptr<FieldUnit>> combinedVector = playerArmy_.getUnits();
    combinedVector.insert(combinedVector.end(), botArmy_.getUnits().begin(), botArmy_.getUnits().end());
    initiativeQueue = std::make_unique<InitiativeQueue>(combinedVector);
}


void BattleManager::setUnitsInStartingPositions()
{
    
}