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

#include "BattleField.h"
#include "Hex.h"
#include "IManager.h"
#include "HexMap.hpp"

constexpr unsigned int BATTLE_HEX_WIDTH = 15;
constexpr unsigned int BATTLE_HEX_HEIGHT = 11;


class BattleManager : public IManager
{
public:
    BattleManager();
    BattleManager(const std::vector<Unit>& playerArmy, const std::vector<Unit>& enemyArmy, HexMap<Tile> map);
    std::vector<std::shared_ptr<FieldUnit>> getAllUnits() const;
    const std::string& getBackground() const;
    void accept(RendersVisitator& visitor) const override;
private:
    BattleField field_;
    HexMap<Tile> map_;
    std::string background_;

    void setUnitsInStartingPositions();
};