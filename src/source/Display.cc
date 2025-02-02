/*
 * File:        Display.cc
 * Description: Responsible for rendering textures using SDL library
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */

#include <iostream>
#include <algorithm>
#include "Display.h"
#include "Logger.h"
#include "SDL2/SDL_image.h"
#include "IManager.h"
#include "IRenderable.h"
#include "GridPositionParser.h"
#include "ResourceCounter.h"


Display::Display()
    : window_(nullptr), renderer_(nullptr), texture_manager_()
{
    initFont();
}

Display::~Display()
{
    clean();
}

void Display::init(const char* window_title, int window_width, int window_height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        throw std::runtime_error("SDL init error: " + std::string(SDL_GetError()));
    }

    window_ = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
}

void Display::render(const IManager& manager)
{
    if(renderer_ == nullptr)
    {
        Logger::warning("Display.render(): Render pointer is nullptr");
        return;
    }
    SDL_RenderClear(renderer_);
    
    manager.accept(*this);
    sortRenders(objects_to_render_);

    switch (scene_type_)
    {
    case SceneType::BATTLE:
        renderBattle();
        break;
    case SceneType::MAP:
        sortRenders(decorations_to_render_);
        renderMap();
        renderResources();
        if(ResourceCounter::getInstance().allResourcesCollected())
        {
            rednerVictoryScreen();
        }
        break;
    default:
        Logger::error("Non existant scene type render request");
        break;
    }

    SDL_RenderPresent(renderer_);
}

void Display::clean()
{
    if(renderer_ == nullptr)
    {
        Logger::warning("Display.clean(): Render pointer is nullptr");
    }

    if(window_ == nullptr)
    {
        Logger::warning("Display.clean(): Window pointer is nullptr");
    }
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
}

void Display::renderBattle()
{
    // Render Background
    try{
        const Texture& render_texture = texture_manager_.getTexture(background_, renderer_);
        SDL_RenderCopy(renderer_, render_texture.getTexture(), NULL, NULL);
    }
    catch(const std::runtime_error& e){
           Logger::error(e.what());
    }

    // Render Grid
    try{
        for(int row = 0; row < grid_dimensions_.r; ++row)
        {
            for(int col = 0; col < grid_dimensions_.q; ++col)
            {
                SDL_Texture* texture = texture_manager_.getTexture(BATTLE_GRID_IDLE_PATH, renderer_).getTexture();
                SDL_Rect destR = makeBattleCellRect(Hex(col, row));
                SDL_RenderCopy(renderer_, texture, NULL, &destR);
            }
        }
    }
    catch(const std::runtime_error& e){
           Logger::error(e.what());
    }

    // Render Objects
    for (const auto& render : objects_to_render_) {
        try{
            SDL_Texture* texture = texture_manager_.getTexture(render->getSpritePath(), renderer_).getTexture();
            SDL_Rect destR = makeRectFromRenderable(*render);
            SDL_RendererFlip flip = render->isFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            SDL_RenderCopyEx(renderer_, texture, NULL, &destR, 0, NULL, flip);
        }
        catch(const std::runtime_error& e){
            Logger::error(e.what());
        }
    }
}

void Display::renderMap()
{
    // Ground
    for (const auto& render : objects_to_render_) {
        try{
            SDL_Texture* texture = texture_manager_.getTexture(render->getSpritePath(), renderer_).getTexture();
            SDL_Rect destR = makeMapCellRect(*render);
            SDL_RendererFlip flip = render->isFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            SDL_RenderCopyEx(renderer_, texture, NULL, &destR, 0, NULL, flip);
        }
        catch(const std::runtime_error& e){
            Logger::error(e.what());
        }
    }

    // Decorations
    for (const auto& render : decorations_to_render_) {
        try{
            SDL_Texture* texture = texture_manager_.getTexture(render->getSpritePath(), renderer_).getTexture();
            SDL_Rect destR = makeMapObjectRect(*render);
            SDL_RendererFlip flip = render->isFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            SDL_RenderCopyEx(renderer_, texture, NULL, &destR, 0, NULL, flip);
        }
        catch(const std::runtime_error& e){
            Logger::error(e.what());
        }
    }

}

void Display::sortRenders(std::vector<const IRenderable*>& objects)
{
    std::sort(objects.begin(), objects.end(), [](const IRenderable* a, const IRenderable* b) {
        if (a->getSpritePriority() != b->getSpritePriority()) {
            return a->getSpritePriority() < b->getSpritePriority();
        } else {
            return a->getPosition().r < b->getPosition().r;
        }
    });
}
SDL_Rect Display::makeRectFromRenderable(const IRenderable& render) const
{
    SDL_Rect retRect;
    Hex pos = GridPositionParser::parseGridToPosition(
                                        GridPositionParser::axialToOddr(render.getPosition()), 
                                        Hex(BATTLE_GRID_CELL_SIZE, BATTLE_GRID_CELL_HEIGHT), 
                                        Hex(BATTLE_GRID_ANCHOR_X, BATTLE_GRID_ANCHOR_Y),
                                        Hex(BATTLE_OFFSET_X, BATTLE_OFFSET_Y), 
                                        BATTLE_GRID_EVEN_ROW_INDENT);
    retRect.h = render.getSpriteDimensions().r;
    retRect.w = render.getSpriteDimensions().q;
    retRect.x = pos.q;
    retRect.y = pos.r;
    return retRect;
}

SDL_Rect Display::makeBattleCellRect(const Hex& position) const
{
    SDL_Rect retRect;
    Hex pos = GridPositionParser::parseGridToPosition(position, 
                                        Hex(BATTLE_GRID_CELL_SIZE, BATTLE_GRID_CELL_HEIGHT), 
                                        Hex(BATTLE_GRID_ANCHOR_X, BATTLE_GRID_ANCHOR_Y),
                                        Hex(0,0),
                                        BATTLE_GRID_EVEN_ROW_INDENT);
    retRect.h = BATTLE_GRID_CELL_SIZE;
    retRect.w = BATTLE_GRID_CELL_SIZE;
    retRect.x = pos.q;
    retRect.y = pos.r;
    return retRect;
}

SDL_Rect Display::makeMapCellRect(const IRenderable& render) const
{
    SDL_Rect retRect;
    Hex pos = GridPositionParser::parseGridToPosition(render.getPosition(), 
                                        Hex(MAP_GRID_CELL_SIZE, MAP_GRID_CELL_SIZE), 
                                        Hex(0,0),
                                        Hex(0,0),
                                        0);
    retRect.h = MAP_GRID_CELL_SIZE;
    retRect.w = MAP_GRID_CELL_SIZE;
    retRect.x = pos.q;
    retRect.y = pos.r;
    return retRect;
}

SDL_Rect Display::makeMapObjectRect(const IRenderable& render) const
{
    SDL_Rect retRect;
    Hex pos = GridPositionParser::parseGridToPosition(render.getPosition(),
                                        Hex(MAP_GRID_CELL_SIZE, MAP_GRID_CELL_SIZE),
                                        Hex(0,0),
                                        Hex(0,0),
                                        0);
    retRect.h = render.getSpriteDimensions().r;
    retRect.w = render.getSpriteDimensions().q;
    retRect.x = pos.q;
    retRect.y = pos.r;
    return retRect;
}


void Display::renderResources()
{
    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    SDL_Rect redSquare = { 0, 0, 800, 25 };
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_RenderFillRect(renderer_, &redSquare);

    // Load font
    int offset = RESOURCE_INIT_POS_X;
    for (const auto& entry : ResourceCounter::getInstance().getAllResources())
    {
        std::stringstream ss;
        ss << entry.first << ": " << entry.second;
        std::string text = ss.str();

        SDL_Surface* textSurface = TTF_RenderText_Solid(font_, text.c_str(), textColor);
        if (!textSurface)
        {
            Logger::error("Failed to create text surface: " + std::string(TTF_GetError()));
            
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
        if (!textTexture)
        {
            Logger::error("Failed to create text texture: " + std::string(SDL_GetError()));
            SDL_FreeSurface(textSurface);
            return;
        }

        SDL_Rect textRect = { offset, RESOURCE_FONT_HEIGHT, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer_, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
        offset += RESOURCE_SPACING;
    }
}

void Display::rednerVictoryScreen()
{
    int popupX = 200;
    int popupY = 250;
    int popupWidth = 400;
    int popupHeight = 50;

    // Define text properties
    const char* victoryText = "Zdobyles wszystkie zasoby, wygrywasz!";
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_SetRenderDrawColor(renderer_, 50, 50, 50, 200);
    SDL_Rect popup = { popupX, popupY, popupWidth, popupHeight };
    SDL_RenderFillRect(renderer_, &popup);
    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer_, &popup);
    // Make Text Surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font_, victoryText, textColor);
    if (textSurface == nullptr) {
        std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
        return;
    }
    // Make Text Texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
    SDL_FreeSurface(textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
        return;
    }
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    int textX = popupX + (popupWidth - textWidth) / 2;
    int textY = popupY + (popupHeight - textHeight) / 2 + 3;
    SDL_Rect textRect = { textX, textY, textWidth, textHeight };
    SDL_RenderCopy(renderer_, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}

void Display::initFont()
{
    if (TTF_Init() == -1) 
    {
        Logger::error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
        return;
    }
    font_ = TTF_OpenFont("media/fonts/pixel_font.ttf", 12);
    if (!font_) 
    {
        Logger::error("Could not load font: " + std::string(TTF_GetError()));
        TTF_Quit();
        return;
    }
}


