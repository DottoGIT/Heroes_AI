#include <stdexcept>
#include "TextureManager.h"

const Texture &TextureManager::get_texture(const std::string& identifier, SDL_Renderer* renderer)
{
    auto it = texture_cache.find(identifier);
    if (it != texture_cache.end())
        return it->second;
    auto emplaced = texture_cache.emplace(identifier, identifier, renderer);
    if (emplaced.second) {
        return emplaced.first->second;
    }
    throw std::runtime_error("Error! Couldn't get texture! Unknown exception!");
}

bool TextureManager::preloadTexture(const std::string &identifier, SDL_Renderer *renderer)
{
    auto emplaced = texture_cache.emplace(identifier, identifier, renderer);
    bool& success = emplaced.second;
    return success;
}
