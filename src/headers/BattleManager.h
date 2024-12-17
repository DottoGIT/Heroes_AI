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
#include <vector>

#include "Hex.h"
#include "FieldArmy.h"
#include "IManager.h"
#include "InitiativeQueue.h"
#include "FieldUnit.h"
#include "HexMap.hpp"

constexpr unsigned int BATTLE_HEX_WIDTH = 15;
constexpr unsigned int BATTLE_HEX_HEIGHT = 11;


class BattleManager : public IManager
{
public:
    BattleManager();
    BattleManager(const FieldArmy& playerArmy, const FieldArmy& botArmy);

    std::vector<std::shared_ptr<FieldUnit>> getAllUnits() const;
    const std::string& getBackground() const;
    Hex getBattleGridDimensions() const;

    void accept(RendersVisitator& visitor) const override;
private:
    FieldArmy playerArmy_;
    FieldArmy botArmy_;
    HexMap<std::shared_ptr<FieldUnit>> map_;
    InitiativeQueue initiativeQueue_;
    std::string background_;

    void setInitiativeQueue();
    void setUnitsInStartingPositions();
};