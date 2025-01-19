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

    isRunning_ = false;
    currentScene_ = SceneType::Map;

    ///////////////////////////////////////////////////////////
    /* DEVELOPMENT ONLY CREATION OF BATTLE UNITS AND MANAGER */
    ///////////////////////////////////////////////////////////

    // Unit factory
    FieldUnitFactory unit_factory;
    // Init battle manager
    FieldArmy playerArmy(ArmyType::Player);
    auto archer = unit_factory.CreateUnit(UnitType::Archer, 20);
    archer->setPosition(Hex(0, 0));
    auto swordsman = unit_factory.CreateUnit(UnitType::Swordsman, 30);
    swordsman->setPosition(Hex(1, 1));
    playerArmy.addUnit(archer);
    playerArmy.addUnit(swordsman);

    FieldArmy computerArmy(ArmyType::Computer);
    auto enchanter = unit_factory.CreateUnit(UnitType::Enchanter, 20);
    enchanter->setPosition(Hex(14, 10));
    auto skeleton = unit_factory.CreateUnit(UnitType::Skeleton, 30);
    skeleton->setPosition(Hex(14, 9));
    computerArmy.addUnit(enchanter);
    computerArmy.addUnit(skeleton);
    // Battlemanager
    battleManager_ = std::make_unique<BattleManager>(playerArmy, computerArmy);
    
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
    isRunning_ = true;

    return 0;
}

void HeroesAI::start()
{
    Uint64 frame_start;
    Uint64 frame_time;

    while(isRunning_)
    {
        frame_start = SDL_GetPerformanceCounter();

        handleEvents();
        update();
        render();

        // Wait for stable frame rate
        frame_time = (SDL_GetPerformanceCounter() - frame_start) / SDL_GetPerformanceFrequency();
        if(frame_time < FRAME_RATE)
        {
            SDL_Delay(Uint32(FRAME_RATE - frame_time) * 1000);
        }
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
            isRunning_ = false;
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
    if(mapManager_ == nullptr || battleManager_ == nullptr)
    {
        Logger::error("Not All Managers are Set");
    }

    switch (currentScene_)
    {
    case SceneType::Map:
        display_->render(*mapManager_);
        break;
    case SceneType::Battle:
        display_->render(*battleManager_);
        break;
    default:
        Logger::error("Unrecognized Scene Type: ");
    }
}
