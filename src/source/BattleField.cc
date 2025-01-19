#include "BattleField.h"
#include <algorithm>

BattleField::BattleField()
{}

BattleField::BattleField(FieldArmy player, FieldArmy enemy, HexMap<Tile> *map)
    : player_(std::move(player)), enemy_(std::move(enemy)), queue_(player_, enemy_), map_(map)
{}

const FieldArmy &BattleField::getPlayer() const
{
    return player_;
}

const FieldArmy &BattleField::getEnemy() const
{
    return enemy_;
}

const HexMap<Tile> *BattleField::getMap() const
{
    return map_;
}

const InitiativeQueue &BattleField::getQueue() const
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
    
    auto walk_tiles = map_->getReachableTiles(current_unit.getPosition(), [this](Hex hex) {
        return this->getMap()->at(hex) == Tile::REACHABLE;
        for (const FieldUnit& unit : this->getPlayer().getUnits()) {
            if (unit.getPosition() == hex) return false;
        }
        for (const FieldUnit& unit : this->getEnemy().getUnits()) {
            if (unit.getPosition() == hex) return false;
        }
        return true;
    }, current_unit.getWalkRange().get());

    for (Hex Move_tile : walk_tiles) {
        
    }
}
