/*
 * File:        main.cc
 * Description: boot file for project
 * 
 * Author:      Maciej Scheffer
 * Date:        01.11.2024
 */

#include <memory>
#include "HeroesAI.h"
#include "Logger.h"

int main(int argc, char* argv[]) 
{
    Logger::info("Game is starting...");
    HeroesAI heroesAI;
    
    if(heroesAI.init() != 0)
    {
        Logger::error("HeroesAI failed to initialize, exiting");
        return 1;
    }

    Logger::info("Game loop started");
    heroesAI.start();

    Logger::info("Game ended");
    return 0;
}
