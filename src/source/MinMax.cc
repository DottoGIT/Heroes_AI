#include <algorithm>
#include <limits>
#include <iostream>
#include "MinMax.h"
#include "BattleField.h"

constexpr int UNIT_TYPE_KEY = 128873;
constexpr int ARMY_TYPE_KEY = 144961;
constexpr int MOVE_TYPE_KEY = 202973;

MinMax::MinMax()
    : transposition_hits_(0)
{
}

MinMax::MinMax(const BattleField &battlefield)
    : transposition_hits_(0)
{
}

int MinMax::evaluate(const BattleField &battlefield) const
{
    ArmyType is_winner = battlefield.whoWon();
    if (is_winner == ArmyType::COMPUTER)
        return std::numeric_limits<int>::min();
    if (is_winner == ArmyType::PLAYER)
        return std::numeric_limits<int>::max();
    
    int enemy_strength = 0;
    for (const FieldUnit& unit : battlefield.getEnemy().getUnits())
        enemy_strength += unit.getAttackStrength().get() * unit.getHealth().get();
    int player_strength = 0;
    for (const FieldUnit& unit : battlefield.getPlayer().getUnits())
        player_strength += unit.getAttackStrength().get() * unit.getHealth().get();
    
    return player_strength - enemy_strength;
}

UnitMove MinMax::minMax(BattleField battlefield, int depth)
{
    transposition_table_.clear();
    transposition_hits_ = 0;
    position_checked_ = 0;
    auto result = minMax(std::move(battlefield), depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    return result.first;
}

int MinMax::getTranspositionTableHits() const
{
    return transposition_hits_;
}

int MinMax::getPositionsCheckedCount() const
{
    return position_checked_;
}

std::pair<UnitMove, int> MinMax::minMax(BattleField battlefield, int depth, int alpha, int beta)
{
    size_t hashed_battlefield = hashField(battlefield);
    auto it = getTranspositionEntry(hashed_battlefield, depth);
    if (it != transposition_table_.end()) {
        return {UnitMove(), it->second.score};
    }

    if (depth == 0 || battlefield.whoWon() != ArmyType::NONE) {
        return {UnitMove(), evaluate(battlefield)};
    }

    UnitMove best_move;
    int best_score;
    if (battlefield.getQueue().current().type == ArmyType::PLAYER) {

        best_score = std::numeric_limits<int>::min();
        std::vector<UnitMove> moves = battlefield.getMoves();

        for (const UnitMove& move : moves)
        {
            BattleField newBattlefield = battlefield.makeMove(move);
            std::pair<UnitMove, int> result = minMax(std::move(newBattlefield), depth - 1, alpha, beta);
            if (result.second > best_score)
            {
                best_move = move;
                best_score = result.second;
            }
            alpha = std::max(alpha, best_score);
            if (beta <= alpha)
                break;
        }
    }
    else
    {
        best_score = std::numeric_limits<int>::max();
        std::vector<UnitMove> moves = battlefield.getMoves();

        for (const UnitMove& move : moves)
        {
            BattleField newBattlefield = battlefield.makeMove(move);
            std::pair<UnitMove, int> result = minMax(std::move(newBattlefield), depth - 1, alpha, beta);
            if (result.second < best_score)
            {
                best_move = move;
                best_score = result.second;
            }
            beta = std::min(beta, best_score);
            if (beta <= alpha)
                break;
        }
    }
    position_checked_ += 1;
    transposition_table_[hashed_battlefield] = TranspositionEntry{best_score, depth};
    return {best_move, best_score};
}

std::unordered_map<size_t, TranspositionEntry>::iterator MinMax::getTranspositionEntry(size_t hashed_battlefield, const int curr_depth)
{
    auto it = transposition_table_.find(hashed_battlefield);
    if (it == transposition_table_.end())
        return transposition_table_.end();
    if (it->second.depth < curr_depth)
        return transposition_table_.end();
    transposition_hits_ += 1;
    return it;
}

size_t MinMax::hashHex(const Hex &hex) const
{
    size_t hashed = 0;
    hashed ^= std::hash<int>()(hex.q);
    hashed ^= std::hash<int>()(hex.r);
    return hashed;
}

size_t MinMax::hashUnit(const FieldUnit &unit) const
{
    size_t hashed = 0;

    hashed ^= std::hash<int>()(static_cast<int>(unit.getUnitType()) ^ UNIT_TYPE_KEY);
    hashed ^= std::hash<int>()(unit.getHealth().get());
    hashed ^= hashHex(unit.getPosition());

    return hashed;
}

size_t MinMax::hashIndex(const FieldUnitIndex &unit_index) const
{
    size_t hashed = 0;
    hashed ^= std::hash<int>()(static_cast<int>(unit_index.type) ^ ARMY_TYPE_KEY);
    hashed ^= std::hash<uint32_t>()(unit_index.index);
    return hashed;
}

size_t MinMax::hashArmy(const FieldArmy &army) const
{
    size_t hashed = 0;
    size_t index = 0;

    for (const FieldUnit& unit : army.getUnits())
    {
        size_t hashed_unit = hashUnit(unit);
        hashed ^= (hashed_unit ^ ((index + 1) * 17)) * 31;
        ++index;
    }
    return hashed;
}

size_t MinMax::hashQueue(const InitiativeQueue &queue) const
{
    size_t hashed = 0;
    size_t index = 0;
    for (const FieldUnitIndex& field_index : queue.getQueue()) 
    {
        size_t hashed_index = hashIndex(field_index);
        hashed ^= (hashed_index ^ ((index + 1) * 17)) * 31;
        ++index;
    }
    return hashed;
}

size_t MinMax::hashField(const BattleField &battlefield) const
{
    size_t hashed = 0;
    hashed ^= std::hash<int>()(static_cast<int>(battlefield.getCurrentMoveType()) ^ MOVE_TYPE_KEY);
    hashed ^= hashArmy(battlefield.getPlayer()) ^ std::hash<int>()(static_cast<int>(ArmyType::PLAYER) ^ ARMY_TYPE_KEY);
    hashed ^= hashArmy(battlefield.getEnemy()) ^ std::hash<int>()(static_cast<int>(ArmyType::COMPUTER) ^ ARMY_TYPE_KEY);
    hashed ^= hashQueue(battlefield.getQueue());
    return hashed;
}
