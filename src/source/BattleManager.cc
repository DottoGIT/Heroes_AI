#include "BattleManager.h"
#include "RendersVisitator.h"
#include "Logger.h"

BattleManager::BattleManager(const FieldArmy& playerArmy, const FieldArmy& botArmy)
: playerArmy_(playerArmy), botArmy_(botArmy)
{
    setInitiativeQueue();
    setUnitsInStartingPositions();
    createHexMap();

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