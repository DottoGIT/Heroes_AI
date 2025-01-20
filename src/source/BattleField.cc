/*
 * File:        BattleField.cc
 * Description: Manages Unit actions in battle.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        17.01.2025
 */

#include <algorithm>
#include "BattleField.h"

BattleField::BattleField()
{}

BattleField::BattleField(FieldArmy player, FieldArmy enemy, HexMap<Tile> *map)
    : player_(std::move(player)), enemy_(std::move(enemy)), queue_(player_, enemy_), map_(map), current_move_(MoveType::Move)
{}

const MoveType BattleField::getCurrentMoveType() const
{
    return current_move_;
}

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
    if (current_move_ == MoveType::Move) {
        return getMoveMoves();
    }
    return getAttackMoves();
}

BattleField BattleField::makeMove(const UnitMove unit_move) const
{
    BattleField nextState(player_, enemy_, map_);
    if (unit_move.getType() == MoveType::Move) {
        nextState.move(unit_move.getTarget());
    } else if (unit_move.getType() == MoveType::Attack) {
        nextState.attack(unit_move.getTarget());
    } else {
        nextState.wait();
    }
    return nextState;
}

void BattleField::attack(const Hex target)
{
    FieldUnitIndex current = queue_.current();
    unsigned damage = activeUnit().getAttackStrength().get();
    auto it = std::find_if(passiveArmy().begin(), passiveArmy().end(),
        [target](const FieldUnit& unit) {
            return target == unit.getPosition();
    });
    if (it == passiveArmy().end())
        throw std::out_of_range("No attack target at position");
    it->takeDamage(damage);
    current_move_ = MoveType::Move;
    queue_.next();
}

void BattleField::move(const Hex target)
{
    activeUnit().setPosition(target);
    current_move_ = MoveType::Attack;
}

void BattleField::wait()
{
    if (current_move_ == MoveType::Attack) queue_.next();
    current_move_ = (current_move_ == MoveType::Attack) ? MoveType::Move : MoveType::Attack;
}

std::vector<UnitMove> BattleField::getAttackMoves() const
{
    std::vector<UnitMove> possible_moves;
    possible_moves.push_back(UnitMove::wait());

    unsigned attack_range = activeUnit().getAttackRange().get();
    const Hex current_position = activeUnit().getPosition();
    
    for (const FieldUnit& attacked_unit : passiveArmy().getUnits()) {
        if (current_position.distance(attacked_unit.getPosition()) <= attack_range)
            possible_moves.push_back(UnitMove::attack(attacked_unit.getPosition()));
    }
    return possible_moves;
}

std::vector<UnitMove> BattleField::getMoveMoves() const
{
    std::vector<UnitMove> possible_moves;
    possible_moves.push_back(UnitMove::wait());

    unsigned move_range = activeUnit().getWalkRange().get();
    const Hex current_position = activeUnit().getPosition();

    std::vector<Hex> move_positions = map_->getReachableTiles(current_position,
    [this](Hex position) {
        if (map_->at(position) == Tile::UNREACHABLE) return false;
        auto lambda = [&](const FieldUnit& unit) {return unit.getPosition() == position;};
        auto it = std::find_if(player_.cbegin(), player_.cend(), lambda);
        if (it == player_.cend()) return false;
        it = std::find_if(enemy_.cbegin(), enemy_.cend(), lambda);
        if (it == enemy_.cend()) return false;
        return true;
    }, move_range);
    for (const Hex& hex : move_positions) possible_moves.push_back(UnitMove::move(hex));
    return possible_moves;
}

FieldArmy &BattleField::activeArmy()
{
    FieldUnitIndex current = queue_.current();
    return (current.type == ArmyType::Player) ? player_ : enemy_;
}

const FieldArmy &BattleField::activeArmy() const
{
    FieldUnitIndex current = queue_.current();
    return (current.type == ArmyType::Player) ? player_ : enemy_;
}

FieldArmy &BattleField::passiveArmy()
{
    FieldUnitIndex current = queue_.current();
    return (current.type != ArmyType::Player) ? player_ : enemy_;
}

const FieldArmy &BattleField::passiveArmy() const
{
    FieldUnitIndex current = queue_.current();
    return (current.type != ArmyType::Player) ? player_ : enemy_;
}

FieldUnit &BattleField::activeUnit()
{
    FieldUnitIndex current = queue_.current();
    return activeArmy().at(current.index);
}

const FieldUnit &BattleField::activeUnit() const
{
    FieldUnitIndex current = queue_.current();
    return activeArmy().getUnits().at(current.index);
}
