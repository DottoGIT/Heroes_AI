/*
 * File:        BattleManager.h
 * Description: Sets up battle field, and manages battle flow.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include <queue>
#include <memory>

#include "Hex.h"

constexpr unsigned int BATTLE_HEX_WIDTH = 15;
constexpr unsigned int BATTLE_HEX_HEIGHT = 11;

class InitiativeQueue;
class FieldArmy;
class FieldUnit;
template <typename T> class HexMap;

class BattleManager{
public:
    BattleManager(FieldArmy& playerArmy, FieldArmy& botArmy);
private:
    FieldArmy& playerArmy_;
    FieldArmy& botArmy_;
    std::unique_ptr<HexMap<std::shared_ptr<FieldUnit>>> map_;
    std::unique_ptr<InitiativeQueue> initiativeQueue;

    void setInitiativeQueue();
    void createHexMap();
    void setUnitsInStartingPositions();
};