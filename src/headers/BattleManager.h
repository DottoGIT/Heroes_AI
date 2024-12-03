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

<<<<<<< HEAD
#include "Hex.hpp"
#include "RenderObject.h"
#include "FieldArmy.h"
#include "IManager.h"
#include "InitiativeQueue.h"
#include "FieldUnit.h"
#include "HexMap.hpp"
=======
#include "Hex.h"
>>>>>>> 7eb794d3b2711d72cca9cbb45a087d6e8b102a40

constexpr unsigned int BATTLE_HEX_WIDTH = 15;
constexpr unsigned int BATTLE_HEX_HEIGHT = 11;


class BattleManager : public IManager
{
public:
    BattleManager();
    void setArmies(const FieldArmy& playerArmy, const FieldArmy& botArmy);
    std::vector<std::shared_ptr<FieldUnit>> getAllUnits() const;
    const std::string& getBackground() const;
    void accept(RendersVisitator& visitor) const override;
private:
    FieldArmy playerArmy_;
    FieldArmy botArmy_;
    std::unique_ptr<HexMap<std::shared_ptr<FieldUnit>>> map_;
    std::unique_ptr<InitiativeQueue> initiativeQueue_;
    std::string background_;

    void setInitiativeQueue();
    void createHexMap();
    void setUnitsInStartingPositions();
};