/*
 * File:        InputController.cc
 * Description: Game mouse input controller
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        16.01.2025
 */

#include <string>
#include <algorithm> 
#include "InputController.h"
#include "Logger.h"


void InputController::processInput(const SDL_Event& event) const
{
    switch(event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            bool leftButton = (event.button.button == SDL_BUTTON_LEFT);
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            
            for (IClickable* observer : mouse_click_observers_) 
            {
                if (observer) 
                {
                    observer->reactToClick(leftButton, Hex(mouseX, mouseY));
                }
            }
            break;
        }
        default:
            break;
    }
}

void InputController::subscribeToMouseClick(IClickable* observer) {
    if (observer && std::find(mouse_click_observers_.begin(), mouse_click_observers_.end(), observer) == mouse_click_observers_.end()) 
    {
        mouse_click_observers_.push_back(observer);
    }
}

void InputController::unsubscribeFromMouseClick(IClickable* observer) {
    mouse_click_observers_.erase
    (
        std::remove(mouse_click_observers_.begin(), mouse_click_observers_.end(), observer),
        mouse_click_observers_.end()
    );
}