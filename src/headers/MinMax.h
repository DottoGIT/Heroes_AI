#pragma once
#include "BattleField.h"

class MinMax
{
private:
public:
    MinMax();
    MinMax(const BattleField& battlefield);
    int evaluate(const BattleField& battlefield) const;
    std::pair<UnitMove, int> minMax(BattleField battlefield, int depth, int alpha, int beta);
};