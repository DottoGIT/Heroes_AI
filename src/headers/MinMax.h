/*
 * File:        MinMax.h
 * Description: Implements MinMax algorithm for BattleField with alpha-beta pruning
 *              and a transposition table.
 *
 * Authors:     Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        18.01.2025
 */

#pragma once
#include "BattleField.h"

struct TranspositionEntry
{
    int score;
    int depth;
};


class MinMax
{
private:
    using transposition_map_t = std::unordered_map<size_t, TranspositionEntry>;
    transposition_map_t transposition_table_;
    int transposition_hits_;
    int position_checked_;
    int branches_pruned_;
public:
    MinMax();
    MinMax(const BattleField& battlefield);
    int evaluate(const BattleField& battlefield) const;
    UnitMove minMax(BattleField battlefield, int depth);
    int getTranspositionTableHits() const;
    int getPositionsCheckedCount() const;
    int getBranchesPruned() const;
private:
    std::pair<UnitMove, int> minMax(BattleField battlefield, int depth, int alpha, int beta);
    transposition_map_t::iterator getTranspositionEntry(size_t hashed_battlefield, const int curr_depth);
    size_t hashHex(const Hex& hex) const;
    size_t hashUnit(const FieldUnit& unit) const;
    size_t hashIndex(const FieldUnitIndex& unit_index) const;
    size_t hashArmy(const FieldArmy& army) const;
    size_t hashQueue(const InitiativeQueue& queue) const;
    size_t hashField(const BattleField& battlefield) const;
};