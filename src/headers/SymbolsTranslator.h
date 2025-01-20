/*
 * File:        SymbolsTranslator.h
 * Description: Maps one letter symbols to existing sprite paths.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#pragma once

#include <map>
#include <string>
#include <memory>
#include "Hex.h"
#include "IInteractable.h"
#include "FieldArmy.h"

class SymbolsTranslator {
public:
    static std::map<char, std::string> symbolsToPaths;
    static std::map<char, Hex> symbolsToSizes;
    static std::map<char, std::shared_ptr<IInteractable>> symbolsToObjects;
    FieldArmy createArmyFromSymbol(char s);
};

