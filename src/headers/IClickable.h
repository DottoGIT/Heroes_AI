/*
 * File:        IClickable.h
 *
 * Description: Interface for objects that can react to clicking 
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        16.01.2025
 */
#pragma once
#include "Hex.h"

class IClickable {
public:
    virtual ~IClickable() = default;
    virtual void reactToClick(bool left_button, const Hex& click_position) = 0;
};