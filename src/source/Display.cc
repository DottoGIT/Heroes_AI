#include "Display.h"

#include <iostream>
#include <algorithm>
#include "HeroesAIExcept.h"
#include "Logger.h"
#include "SDL2/SDL_image.h"
#include "IManager.h"
#include "IRenderable.h"


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
    renderObjects();

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

void Display::renderObjects()
{
    // Render Background
    Logger::debug("Trying to render: " + background_);
    try{
        const Texture& render_texture = texture_manager_.get_texture(background_, renderer_);
        SDL_RenderCopy(renderer_, render_texture.getTexture(), NULL, NULL);
    }
    catch(const std::runtime_error& e){
           Logger::error(e.what());
    }

    // Render Objects
    for (const auto& render : objects_to_render_) {
        Logger::debug("Trying to render: " + render->getSpritePath() + ", at priority: " + std::to_string(render->getPriority()));
        try{
            const Texture& object_texture = texture_manager_.get_texture(render->getSpritePath(), renderer_);
            SDL_RenderCopy(renderer_, object_texture.getTexture(), NULL, NULL);
        }
        catch(const std::runtime_error& e){
            Logger::error(e.what());
        }
    }
}

void Display::sortRenders()
{
    std::sort(objects_to_render_.begin(), objects_to_render_.end(), [](const std::shared_ptr<IRenderable>& a, const std::shared_ptr<IRenderable>& b) {
        return a->getPriority() > b->getPriority();
    });
}
