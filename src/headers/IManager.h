/*
 * File:        IManager.h
 * Description: Interface for managers including accept method for visitors
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        02.12.2024
 */

#pragma once
#include <string>

class RendersVisitator;

class IManager
{
public:
    virtual ~IManager() = default;
    virtual void accept(RendersVisitator& visitor) const = 0;
};

