/*
 * File:        HeroesAI.h
 * Description: Game loop for heroes AI
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */

#pragma once

#include <string>
#include <memory>

#include "Display.h"
#include "MapManager.h"
#include "BattleManager.h"
#include "SceneType.h"

constexpr const char* WINDOW_TITLE = "Heroes AI";
constexpr int WINDOW_HEGIHT = 566; // Keep 16/9 ratio
constexpr int WINDOW_WIDTH = 800;

class HeroesAI
{
public:
    HeroesAI();
    ~HeroesAI();

    int init();
    void start();

private:
    void handleEvents();
    void update();
    void render();
    
    bool isRunning_;
    SceneType currentScene_;

    std::unique_ptr<Display> display_;
    std::unique_ptr<MapManager> mapManager_;
    std::unique_ptr<BattleManager> battleManager_;
};