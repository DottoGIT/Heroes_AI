/*
 * File:        InputController.h
 * Description: Game mouse input controller
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        16.01.2025
 */

#pragma once
#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "IClickable.h"

class InputController
{
public:
    InputController() = default;
    ~InputController() = default;
    void processInput(const SDL_Event& event) const;
    void subscribeToMouseClick(IClickable* observer);
    void unsubscribeFromMouseClick(IClickable* observer);
private:
    std::vector<IClickable*> mouse_click_observers;
};