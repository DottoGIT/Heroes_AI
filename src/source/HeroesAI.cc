#include "HeroesAI.h"

#include "HeroesAIExcept.h"
#include "Logger.h"
#include "FieldArmy.h"
#include "FieldUnit.h"
#include "UnitFactory.h"
#include "UnitType.h"

HeroesAI::HeroesAI()
{
    display_ = std::make_unique<Display>();
    inputController_ = std::make_shared<InputController>();
    mapManager_ = std::make_unique<MapManager>(inputController_);

    currentScene_ = SceneType::Map;

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
    } catch(const SdlException& e){
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
            inputController_->processInput(event);
            break;
    }
}

void HeroesAI::update()
{

}

void HeroesAI::render()
{
    switch (currentScene_)
    {
    case SceneType::Map:
        if(mapManager_ == nullptr)
        {
            Logger::error("Map Manager is not set");
        }
        display_->render(*mapManager_);
        break;
    case SceneType::Battle:
        if(battleManager_ == nullptr)
        {
            Logger::error("Battle Manager is not set");
        }
        display_->render(*battleManager_);
        break;
    default:
        Logger::error("Unrecognized Scene Type: ");
    }
}

void HeroesAI::initPlayer()
{
    UnitFactory unit_factory;
    auto archer = unit_factory.CreateUnit(UnitType::Archer, 20);
    auto swordsman = unit_factory.CreateUnit(UnitType::Swordsman, 30);
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
