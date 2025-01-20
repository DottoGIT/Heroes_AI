#pragma once
#include "BattleField.h"

class MinMax
{
private:
    /* data */
public:
    MinMax(const BattleField& battlefield);
    float evaluate(const BattleField& battlefield) const;
    BattleField minMax(BattleField battlefield, int depth);
};