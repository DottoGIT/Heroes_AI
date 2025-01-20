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
#include "Hex.h"
#include "SDL_ttf.h"

constexpr int BATTLE_GRID_ANCHOR_X = 0;
constexpr int BATTLE_GRID_ANCHOR_Y = 100;
constexpr int BATTLE_GRID_CELL_SIZE = 52;
constexpr int BATTLE_GRID_CELL_HEIGHT = 39; // Hex rows size, smaller than size (prefferable 3/4)
constexpr int BATTLE_GRID_EVEN_ROW_INDENT = 26; // prefferable (1/2)
constexpr char* BATTLE_GRID_IDLE_PATH = "media/sprites/gridtile.png";
constexpr char* BATTLE_GRID_ACTIVE_PATH = "media/sprites/active_gridtile.png";
constexpr int MAP_GRID_CELL_SIZE = 32;

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
    TTF_Font* font_;
    TextureManager texture_manager_;

    void sortRenders(std::vector<const IRenderable*>& objects);
    void renderBattle();
    void renderMap();
    void renderResources();
    void rednerVictoryScreen();

    void initFont();
    
    SDL_Rect makeRectFromRenderable(const IRenderable& render) const;
    SDL_Rect makeBattleCellRect(Hex position) const;
    SDL_Rect makeMapCellRect(const IRenderable& render) const;
    SDL_Rect makeMapObjectRect(const IRenderable& render) const;
};