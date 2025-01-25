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

BattleField::BattleField(const FieldArmy& player, const FieldArmy& enemy, HexMap<Tile> *map)
    : player_(std::move(player)), enemy_(std::move(enemy)), queue_(player_, enemy_), map_(map), current_move_(MoveType::MOVE)
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
    if (current_move_ == MoveType::MOVE) {
        return getMoveMoves();
    }
    return getAttackMoves();
}

std::vector<Hex> BattleField::getPath(const Hex &end) const
{
    std::vector<Hex> path;

    unsigned move_range = activeUnit().getWalkRange().get();
    const Hex current_position = activeUnit().getPosition();

    path = map_->findPath(current_position, end, 
    [this](Hex position) {
        if (map_->at(position) == Tile::UNREACHABLE) return false;
        auto lambda = [&](const FieldUnit& unit) {return unit.getPosition() == position;};
        auto it = std::find_if(player_.cbegin(), player_.cend(), lambda);
        if (it != player_.cend()) return false;
        it = std::find_if(enemy_.cbegin(), enemy_.cend(), lambda);
        if (it != enemy_.cend()) return false;
        return true;
    }, move_range);
    return path;
}

BattleField BattleField::makeMove(const UnitMove& unit_move) const
{
    BattleField nextState(*this);
    if (unit_move.getType() == MoveType::MOVE) {
        nextState.move(unit_move.getTarget());
    } else if (unit_move.getType() == MoveType::ATTACK) {
        nextState.attack(unit_move.getTarget());
    } else {
        nextState.wait();
    }
    return nextState;
}

void BattleField::attack(const Hex& target)
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
    current_move_ = MoveType::MOVE;
    nextUnit();
}

void BattleField::move(const Hex& target)
{
    activeUnit().setPosition(target);
    current_move_ = MoveType::ATTACK;
}

void BattleField::wait()
{
    if (current_move_ == MoveType::ATTACK) nextUnit();
    current_move_ = (current_move_ == MoveType::ATTACK) ? MoveType::MOVE : MoveType::ATTACK;
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
        if (it != player_.cend()) return false;
        it = std::find_if(enemy_.cbegin(), enemy_.cend(), lambda);
        if (it != enemy_.cend()) return false;
        return true;
    }, move_range);
    for (const Hex& hex : move_positions) possible_moves.push_back(UnitMove::move(hex));
    return possible_moves;
}

FieldArmy &BattleField::activeArmy()
{
    FieldUnitIndex current = queue_.current();
    return (current.type == ArmyType::PLAYER) ? player_ : enemy_;
}

const FieldArmy &BattleField::activeArmy() const
{
    FieldUnitIndex current = queue_.current();
    return (current.type == ArmyType::PLAYER) ? player_ : enemy_;
}

FieldArmy &BattleField::passiveArmy()
{
    FieldUnitIndex current = queue_.current();
    return (current.type != ArmyType::PLAYER) ? player_ : enemy_;
}

const FieldArmy &BattleField::passiveArmy() const
{
    FieldUnitIndex current = queue_.current();
    return (current.type != ArmyType::PLAYER) ? player_ : enemy_;
}

FieldUnit &BattleField::activeUnit()
{
    FieldUnitIndex current = queue_.current();
    return activeArmy().at(current.index);
}

void BattleField::nextUnit()
{
    queue_.next();
    while (!activeUnit().getHealth().isAlive()) queue_.next();
}

const FieldUnit &BattleField::activeUnit() const
{
    FieldUnitIndex current = queue_.current();
    return activeArmy().getUnits().at(current.index);
}

ArmyType BattleField::whoWon() const
{
    if (std::all_of(enemy_.cbegin(), enemy_.cend(),
            [](const FieldUnit& unit) {
                return !unit.getHealth().isAlive();
            })
        ) return ArmyType::COMPUTER;
    
    if (std::all_of(player_.cbegin(), player_.cend(),
            [](const FieldUnit& unit) {
                return !unit.getHealth().isAlive();
            })
        ) return ArmyType::PLAYER;
    return ArmyType::NONE;
}
