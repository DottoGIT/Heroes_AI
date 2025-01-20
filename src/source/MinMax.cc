#include "MinMax.h"
#include "BattleField.h"
#include <algorithm>
#include <cmath>

MinMax::MinMax(const BattleField &battlefield)
{}

float MinMax::evaluate(const BattleField &battlefield) const
{
    if (
        std::all_of(battlefield.getEnemy().cbegin(), battlefield.getEnemy().cend(),
            [](const FieldUnit& unit) {
                return !unit.getHealth().isAlive();
            })
        )
        return -INFINITY;

    if (
        std::all_of(battlefield.getPlayer().cbegin(), battlefield.getPlayer().cend(),
        [](const FieldUnit& unit) {
            return !unit.getHealth().isAlive();
        })
        )
        return INFINITY;
    
    

}

BattleField MinMax::minMax(BattleField battlefield, int depth)
{
    return BattleField();
}
