#pragma once
#include <vector>
#include "FieldArmy.h"
#include "InitiativeQueue.h"
#include "HexMap.hpp"
#include "Tile.h"
#include "UnitMove.h"


class BattleField
{
private:
    FieldArmy player_;
    FieldArmy enemy_;
    InitiativeQueue queue_;
    HexMap<Tile>* map_;
public:
    BattleField();
    BattleField(FieldArmy player, FieldArmy enemy, HexMap<Tile>* map);
    const FieldArmy& getPlayer() const;
    const FieldArmy& getEnemy() const;
    const HexMap<Tile>* getMap() const;
    const InitiativeQueue& getQueue() const;
    std::vector<UnitMove> getMoves() const;
    BattleField makeMove(const UnitMove unit_move) const;
};