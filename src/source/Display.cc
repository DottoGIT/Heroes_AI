#include "Display.h"

#include <iostream>
#include <algorithm>
#include "HeroesAIExcept.h"
#include "Logger.h"
#include "SDL2/SDL_image.h"
#include "IManager.h"


Display::Display()
{

}

Display::~Display()
{
    clean();
}

void Display::init(const char* window_title, int window_width, int window_height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        throw SdlException("SDL init error: " + std::string(SDL_GetError()));
    }

    window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Display::render(const IManager& manager)
{
    if(renderer == nullptr)
    {
        Logger::warning("Display.render(): Render pointer is nullptr");
        return;
    }

    SDL_RenderClear(renderer);

    manager.accept(*this);
    Logger::debug("Size of renderObjects: " + std::to_string(objects_to_render_.size()));
    Logger::debug("Background path: " + background_);

    //sortRenders();
    //renderObjects();

    SDL_RenderPresent(renderer);
}

void Display::clean()
{
    if(renderer == nullptr)
    {
        Logger::warning("Display.clean(): Render pointer is nullptr");
    }

    if(window == nullptr)
    {
        Logger::warning("Display.clean(): Window pointer is nullptr");
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Display::renderObjects()
{

    // SDL_RenderCopy(renderer, background_, NULL, NULL);

    // for (const auto& render : renders_) {
    //     SDL_RenderCopy(renderer, render.getTexture(), nullptr, &render.getRect());
    // }
}

void Display::sortRenders()
{
    std::sort(objects_to_render_.begin(), objects_to_render_.end(), [](const RenderObject& a, const RenderObject& b) {
        return a.priority > b.priority;
    });
}
