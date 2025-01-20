/*
 * File:        BattleField.h
 * Description: Manages Unit actions in battle.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        17.01.2025
 */

#pragma once
#include <vector>
#include "FieldArmy.h"
#include "InitiativeQueue.h"
#include "HexMap.hpp"
#include "Tile.h"
#include "UnitMove.h"

class BattleField
{
public:
    BattleField();
    BattleField(const FieldArmy& player, const FieldArmy& enemy, HexMap<Tile>* map);
    const MoveType getCurrentMoveType() const;
    const FieldArmy& getPlayer() const;
    const FieldArmy& getEnemy() const;
    const HexMap<Tile>* getMap() const;
    const InitiativeQueue& getQueue() const;
    std::vector<UnitMove> getMoves() const;
    BattleField makeMove(const UnitMove& unit_move) const;
    const FieldUnit& activeUnit() const;
    ArmyType whoWon() const;
private:
    MoveType current_move_;
    FieldArmy player_;
    FieldArmy enemy_;
    InitiativeQueue queue_;
    HexMap<Tile>* map_;
    void attack(const Hex& target);
    void move(const Hex& target);
    void wait();
    std::vector<UnitMove> getAttackMoves() const;
    std::vector<UnitMove> getMoveMoves() const;
    FieldArmy& activeArmy();
    const FieldArmy& activeArmy() const;
    FieldArmy& passiveArmy();
    const FieldArmy& passiveArmy() const;
    FieldUnit& activeUnit();
    void nextUnit();
};