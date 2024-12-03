#include "Display.h"

#include <iostream>
#include <algorithm>
#include "HeroesAIExcept.h"
#include "Logger.h"
#include "SDL2/SDL_image.h"
#include "IManager.h"
#include "IRenderable.h"


Display::Display()
{
    texture_manager_ = std::make_unique<TextureManager>();
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

void Display::render(const IManager* manager)
{
    if(renderer == nullptr)
    {
        Logger::warning("Display.render(): Render pointer is nullptr");
        return;
    }

    SDL_RenderClear(renderer);

    manager->accept(*this);
    sortRenders();
    renderObjects();

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
    SDL_Texture* render_texture = nullptr;
    // Render Background
    try{
        render_texture = texture_manager_->get_texture(background_, renderer).getTexture();
    }
    catch(const std::runtime_error& e){
           Logger::error(e.what());
    }
    SDL_RenderCopy(renderer, render_texture, NULL, NULL);
    Logger::debug("Trying to render: " + background_);

    // Render Objects
    for (const auto& render : objects_to_render_) {
        try{
            render_texture = texture_manager_->get_texture(render->getSpritePath(), renderer).getTexture();
        }
        catch(const std::runtime_error& e){
            Logger::error(e.what());
        }
        
        SDL_RenderCopy(renderer, render_texture, NULL, NULL);
        Logger::debug("Trying to render: " + render->getSpritePath() + ", at priority: " + std::to_string(render->getPriority()));
    }
}

void Display::sortRenders()
{
    std::sort(objects_to_render_.begin(), objects_to_render_.end(), [](const std::shared_ptr<IRenderable>& a, const std::shared_ptr<IRenderable>& b) {
        return a->getPriority() > b->getPriority();
    });
}
