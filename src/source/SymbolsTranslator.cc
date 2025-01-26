/*
 * File:        SymbolsTranslator.cc
 * Description: Maps one letter symbols to existing sprite paths.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#include "SymbolsTranslator.h"
#include "Resource.h"
#include "MapEnemy.h"
#include "UnitFactory.h"
#include "UnitType.h"
#include "Army.h"

std::map<char, std::string> SymbolsTranslator::symbolsToPaths
{
    {'0', "media/sprites/map/ground.png"},
    {'1', "media/sprites/map/fog.png"},
    {'2', "media/sprites/map/shore_t.png"},
    {'3', "media/sprites/map/sea.png"},
    {'4', "media/sprites/map/sea_corner.png"},
    {'5', "media/sprites/map/sea_corner_fill.png"},
    {'6', "media/sprites/map/gts.png"},
    {'7', "media/sprites/map/gts_corner.png"},
    {'8', "media/sprites/map/stg_corner.png"},
    {'9', "media/sprites/map/gtsf.png"},
    {'+', "media/sprites/map/shore_tf.png"},
    {'-', "media/sprites/map/sea_cornerf.png"},
    {'=', "media/sprites/map/sea_cornerf_fill.png"},
    {'_', "media/sprites/map/stg_cornerf.png"},
    {')', "media/sprites/map/gts_cornerf.png"},

    {'a', "media/sprites/map/g_hole.png"},
    {'b', "media/sprites/map/town.png"},
    {'c', "media/sprites/map/d_road.png"},
    {'d', "media/sprites/map/cr_road.png"},
    {'e', "media/sprites/map/ttl_road.png"},
    {'f', "media/sprites/map/l_road.png"},
    {'g', "media/sprites/map/dbr_road.png"},
    {'h', "media/sprites/map/dtl_road.png"},
    {'i', "media/sprites/map/ttr_road.png"},
    {'j', "media/sprites/map/coalMine_unoccupied.png"},
    {'k', "media/sprites/map/coalMine_occupied.png"},
    {'l', "media/sprites/map/woodMine_unoccupied.png"},
    {'m', "media/sprites/map/woodMine_occupied.png"},
    {'n', "media/sprites/map/m1.png"},
    {'o', "media/sprites/map/m2.png"},
    {'p', "media/sprites/map/m3.png"},
    {'r', "media/sprites/map/f1.png"},
    {'s', "media/sprites/map/pond.png"},
    {'t', "media/sprites/map/p2.png"},
    {'u', "media/sprites/map/g1.png"},
    
    {'v', "media/sprites/resources/coal.png"},
    {'w', "media/sprites/resources/mercury.png"},
    {'x', "media/sprites/resources/sulfur.png"},
    {'y', "media/sprites/resources/wood.png"},
    {'z', "media/sprites/resources/gems.png"},
    {'A', "media/sprites/resources/gold.png"},
    {'B', "media/sprites/resources/crystal.png"},

    {'C', "media/sprites/skeleton.png"},
    {'D', "media/sprites/swordsman.png"},
    {'E', "media/sprites/enchanter.png"},
    {'F', "media/sprites/archer.png"},
};

std::map<char, Hex> SymbolsTranslator::symbolsToSizes
{
    {'a', Hex(64, 32)},
    {'b', Hex(156, 196)},
    {'c', Hex(32,32)},
    {'d', Hex(32,32)},
    {'e', Hex(32,32)},
    {'f', Hex(32,32)},
    {'g', Hex(32,32)},
    {'h', Hex(32,32)},
    {'i', Hex(32,32)},
    {'j', Hex(95,65)},
    {'k', Hex(95,65)},
    {'l', Hex(154,64)},
    {'m', Hex(154,64)},
    {'n', Hex(192,128)},
    {'o', Hex(128,96)},
    {'p', Hex(128,64)},
    {'r', Hex(128,128)},
    {'s', Hex(160,96)},
    {'t', Hex(96,32)},
    {'u', Hex(64,32)}
};


std::map<char, std::shared_ptr<IInteractable>> SymbolsTranslator::symbolsToObjects
{
    {'0', nullptr},
    {'v', std::make_shared<Resource>(ResourceType::COAL, 1)},
    {'w', std::make_shared<Resource>(ResourceType::MERCURY, 1)},
    {'x', std::make_shared<Resource>(ResourceType::SULFUR, 1)},
    {'y', std::make_shared<Resource>(ResourceType::WOOD, 1)},
    {'z', std::make_shared<Resource>(ResourceType::GEMS, 1)},
    {'A', std::make_shared<Resource>(ResourceType::GOLD, 1000)},
    {'B', std::make_shared<Resource>(ResourceType::CRYSTALS, 1)},

    {'C', std::make_shared<MapEnemy>(SymbolsTranslator::createArmyFromSymbol('C'))},
    {'D', std::make_shared<MapEnemy>(SymbolsTranslator::createArmyFromSymbol('D'))},
    {'E', std::make_shared<MapEnemy>(SymbolsTranslator::createArmyFromSymbol('E'))},
    {'F', std::make_shared<MapEnemy>(SymbolsTranslator::createArmyFromSymbol('F'))},    
};

Army SymbolsTranslator::createArmyFromSymbol(char s)
{
    UnitFactory unit_factory;
    Army army;
    
    switch (s)
    {
    case 'C':
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        break;
    case 'D':
        army.addUnit(unit_factory.CreateUnit(UnitType::SWORDSMAN, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SWORDSMAN, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SWORDSMAN, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SWORDSMAN, 20));
        break;
    case 'E':
        army.addUnit(unit_factory.CreateUnit(UnitType::ENCHANTER, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SKELETON, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SWORDSMAN, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::ARCHER, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::ENCHANTER, 20));
        break;
    case 'F':
        army.addUnit(unit_factory.CreateUnit(UnitType::ARCHER, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SWORDSMAN, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::SWORDSMAN, 20));
        army.addUnit(unit_factory.CreateUnit(UnitType::ARCHER, 20));
        break;
    default:
        break;
    }

    return army;
}
