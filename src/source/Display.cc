#include "Display.h"

#include <iostream>
#include <algorithm>
#include "HeroesAIExcept.h"
#include "Logger.h"
#include "SDL2/SDL_image.h"
#include "IManager.h"
#include "IRenderable.h"
#include "GridPositionParser.h"


Display::Display()
    : window_(nullptr), renderer_(nullptr), texture_manager_()
{}

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
    sortRenders();

    
    switch (scene_type_)
    {
    case SceneType::Battle:
        renderBattle();
        break;
    case SceneType::Map:
        renderMap();
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
        for(int row = 0; row < grid_dimensions_.r; row++)
        {
            for(int col = 0; col < grid_dimensions_.q; col++)
            {
                SDL_Texture* texture = texture_manager_.getTexture(BATTLE_GRID_IDLE_PATH, renderer_).getTexture();
                SDL_Rect destR = makeCellRect(Hex(col, row));
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
            SDL_Rect destR = makeMapObjectRect(*render);
            SDL_RendererFlip flip = render->isFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            SDL_RenderCopyEx(renderer_, texture, NULL, &destR, 0, NULL, flip);
        }
        catch(const std::runtime_error& e){
            Logger::error(e.what());
        }
    }
}

void Display::sortRenders()
{
    std::sort(objects_to_render_.begin(), objects_to_render_.end(), [](const IRenderable* a, const IRenderable* b) {
        if (a->getSpritePriority() != b->getSpritePriority()) {
            return a->getSpritePriority() > b->getSpritePriority();
        } else {
            return a->getPosition().r < b->getPosition().r;
        }
    });
}

SDL_Rect Display::makeRectFromRenderable(const IRenderable& render) const
{
    SDL_Rect retRect;
    Hex pos = GridPositionParser::parse(render.getPosition(), 
                                        Hex(BATTLE_GRID_CELL_SIZE, BATTLE_GRID_CELL_HEIGHT), 
                                        Hex(BATTLE_GRID_ANCHOR_X, BATTLE_GRID_ANCHOR_Y),
                                        Hex(5,-60), 
                                        BATTLE_GRID_EVEN_ROW_INDENT);
    retRect.h = render.getSpriteDimensions().r;
    retRect.w = render.getSpriteDimensions().q;
    retRect.x = pos.q;
    retRect.y = pos.r;
    return retRect;
}

SDL_Rect Display::makeCellRect(Hex position) const
{
    SDL_Rect retRect;
    Hex pos = GridPositionParser::parse(position, 
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

SDL_Rect Display::makeMapObjectRect(const IRenderable& render) const
{
    SDL_Rect retRect;
    Hex pos = GridPositionParser::parse(render.getPosition(), 
                                        render.getSpriteDimensions(), 
                                        Hex(0,0),
                                        Hex(0,0), 
                                        0);
    retRect.h = render.getSpriteDimensions().r;
    retRect.w = render.getSpriteDimensions().q;
    retRect.x = pos.q;
    retRect.y = pos.r;
    return retRect;
}