#include "HeroesAI.h"

#include "HeroesAIExcept.h"
#include "Logger.h"
#include "FieldArmy.h"
#include "FieldUnit.h"
#include "FieldUnitFactory.h"
#include "UnitType.h"

HeroesAI::HeroesAI()
{
    display_ = Display();
    isRunning_ = false;

    // Unit factory
    FieldUnitFactory unit_factory;
    // Init battle manager
    FieldArmy playerArmy(ArmyType::Player);
    playerArmy.addUnit(unit_factory.CreateUnit(UnitType::Archer, 20));
    playerArmy.addUnit(unit_factory.CreateUnit(UnitType::Swordsman, 65));
    FieldArmy computerArmy(ArmyType::Computer);
    computerArmy.addUnit(unit_factory.CreateUnit(UnitType::Skeleton, 100));
    computerArmy.addUnit(unit_factory.CreateUnit(UnitType::Swordsman, 50));
    // Battlemanager
    battleManager_ = BattleManager(playerArmy, computerArmy);
}

HeroesAI::~HeroesAI()
{
    display_.clean();
}

int HeroesAI::init()
{
    try{
        display_.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEGIHT);
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
    while(isRunning_)
    {
        handleEvents();
        update();
        render();
    }
}

void HeroesAI::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            Logger::debug("Quit action detected, stopping the game");
            isRunning_ = false;
            break;
        default:
            break;
    }
}

void HeroesAI::update()
{

}

void HeroesAI::render()
{
    display_.render(battleManager_);
}
