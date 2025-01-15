#include "BattleField.h"
#include <algorithm>

BattleField::BattleField(FieldArmy player, FieldArmy enemy, HexMap<Tile>* map)
    : player_(std::move(player)), enemy_(std::move(enemy)), queue_(player_, enemy_), map_(map)
{}

const FieldArmy &BattleField::getPlayer()
{
    return player_;
}

const FieldArmy &BattleField::getEnemy()
{
    return enemy_;
}

const InitiativeQueue &BattleField::getQueue()
{
    return queue_;
}

std::vector<UnitMove> BattleField::getMoves() const
{
    std::vector<UnitMove> possible_moves;
    possible_moves.emplace_back();
    FieldUnitIndex current = queue_.current();
    const FieldUnit& current_unit = (current.type == ArmyType::Player) ?
        player_.getUnits().at(current.index) :
        enemy_.getUnits().at(current.index);
    auto neighbors = map_->getNeighbors(current_unit.getPosition());
    // TODO:
}
