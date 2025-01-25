/*
 * File:        HeroesAI.cc
 * Description: Game loop for heroes AI
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */

#include <functional>
#include "HeroesAI.h"
#include "Logger.h"
#include "FieldArmy.h"
#include "FieldUnit.h"
#include "UnitFactory.h"
#include "UnitType.h"

HeroesAI::HeroesAI()
{
    display_ = std::make_unique<Display>();
    input_controller_ = std::make_shared<InputController>();
    map_manager_ = std::make_unique<MapManager>(input_controller_, [this](Army* army, const Hex& pos){this->changeModeToBattle(army, pos);});
    current_scene_ = SceneType::MAP;
    initPlayer();
}

HeroesAI::~HeroesAI()
{
    display_->clean();
}

int HeroesAI::init()
{
    try{
        display_->init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEGIHT);
        Logger::debug("SDL window created");
    } catch(const std::exception& e){
        Logger::error(e.what());
        return 1;
    }
    is_running_ = true;

    return 0;
}

void HeroesAI::start()
{
    Uint64 frame_start;

    while(is_running_)
    {
        frame_start = SDL_GetPerformanceCounter();

        handleEvents();
        update();
        render();

        waitForFPS(frame_start);
    }
}

void HeroesAI::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            Logger::debug("Quit Action Detected, Stopping the Game");
            is_running_ = false;
            break;
        default:
            input_controller_->processInput(event);
            break;
    }
}

void HeroesAI::update()
{
    switch (current_scene_)
    {
    case SceneType::BATTLE:
        if(battle_manager_ == nullptr)
        {
            Logger::error("Battle Manager is not set");
        }
        battle_manager_->tryMakeComputerMove();
    default:
        break;
    }
}

void HeroesAI::render()
{
    switch (current_scene_)
    {
    case SceneType::MAP:
        if(map_manager_ == nullptr)
        {
            Logger::error("Map Manager is not set");
        }
        display_->render(*map_manager_);
        break;
    case SceneType::BATTLE:
        if(battle_manager_ == nullptr)
        {
            Logger::error("Battle Manager is not set");
        }
        display_->render(*battle_manager_);
        break;
    default:
        Logger::error("Unrecognized Scene Type: ");
    }
}

void HeroesAI::initPlayer()
{
    UnitFactory unit_factory;
    auto archer = unit_factory.CreateUnit(UnitType::ARCHER, 20);
    auto swordsman = unit_factory.CreateUnit(UnitType::SWORDSMAN, 30);
    player_army_.addUnit(archer);
    player_army_.addUnit(swordsman);
}

void HeroesAI::waitForFPS(Uint64 frame_start)
{
    Uint64 frame_time = (SDL_GetPerformanceCounter() - frame_start) / SDL_GetPerformanceFrequency();
    if(frame_time < FRAME_RATE)
    {
        SDL_Delay(Uint32(FRAME_RATE - frame_time) * 1000);
    }
}

void HeroesAI::changeModeToBattle(Army* enemy_army, const Hex& enemy_pos)
{
    Logger::info("Changing to battle mode");
    HexMap<Tile> map(15, 11);
    std::fill(map.begin(), map.end(), Tile::REACHABLE);
    battle_manager_ = std::make_unique<BattleManager>(player_army_, *enemy_army, map, input_controller_, [](Army* army){});
    current_scene_ = SceneType::BATTLE;
}

void HeroesAI::changeModeToMap()
{
    Logger::info("Change to Map");
}
