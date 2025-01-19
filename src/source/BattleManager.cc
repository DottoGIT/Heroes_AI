#include "BattleManager.h"
#include "RendersVisitator.h"
#include "Logger.h"

namespace {
    std::array<Hex, 7> playerStartPositions = {
        Hex(0, 0),
        Hex(-1, 2),
        Hex()
    };
};

BattleManager::BattleManager()
    : map_(BATTLE_HEX_WIDTH, BATTLE_HEX_HEIGHT)
{}

BattleManager::BattleManager(
    const std::vector<Unit> &playerArmy, const std::vector<Unit> &enemyArmy,
    HexMap<Tile> map
)   : map_(std::move(map))
{
    FieldArmy playerFieldArmy;
    std::for_each(playerArmy.begin(), playerArmy.end(),
        [&, index = 0](const Unit& unit) mutable {
            playerFieldArmy.addUnit(FieldUnit(playerArmy.at(index), playerStartPositions.at(index)));
            index++;
        }
    );
}

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