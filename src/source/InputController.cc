#include "InputController.h"
#include <string>
#include <algorithm> 
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
            
            for (IClickable* observer : mouse_click_observers) 
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
    if (observer && std::find(mouse_click_observers.begin(), mouse_click_observers.end(), observer) == mouse_click_observers.end()) 
    {
        mouse_click_observers.push_back(observer);
    }
}

void InputController::unsubscribeFromMouseClick(IClickable* observer) {
    mouse_click_observers.erase
    (
        std::remove(mouse_click_observers.begin(), mouse_click_observers.end(), observer),
        mouse_click_observers.end()
    );
}