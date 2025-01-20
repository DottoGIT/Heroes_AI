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
#include "InputController.h"

constexpr const char* WINDOW_TITLE = "Heroes AI";
constexpr int WINDOW_HEGIHT = 566; // Keep 16/9 ratio
constexpr int WINDOW_WIDTH = 800;
constexpr Uint64 FRAME_RATE = 1/60; // 60 FPS

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
    void initPlayer();
    void waitForFPS(Uint64 frame_start);
    
    void changeModeToBattle(Army* enemy_army);
    void changeModeToMap();
    
    bool is_running_ = false;
    SceneType current_scene_;
    Army player_army_;
    std::unique_ptr<Display> display_;
    std::shared_ptr<InputController> input_controller_;
    std::unique_ptr<MapManager> map_manager_;
    std::unique_ptr<BattleManager> battle_manager_;
};