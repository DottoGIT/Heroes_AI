/*
 * File:        Display.h
 * Description: Responsible for rendering textures using SDL library
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "RendersVisitator.h"
#include "TextureManager.h"

class IManager;

class Display : public RendersVisitator
{
public:
    Display();
    ~Display();
    void init(const char* window_title, int window_width, int window_height);

    void render(const IManager& manager);
    void clean();

private:
    SDL_Renderer* renderer_;
    SDL_Window* window_;
    TextureManager texture_manager_;
    
    void sortRenders();
    void renderObjects();
};