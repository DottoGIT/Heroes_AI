#include "TextureManager.h"
#include <stdexcept>

const Texture& TextureManager::get_texture(const std::string& identifier, SDL_Renderer* renderer)
{
    auto it = texture_cache.find(identifier);
    if (it != texture_cache.end())
        return it->second;
    auto emplaced = texture_cache.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(identifier),
        std::forward_as_tuple(identifier, renderer));
    if (emplaced.second) {
        return emplaced.first->second;
    }
    throw std::runtime_error("Error! Couldn't get texture! Unknown exception!");
}

bool TextureManager::preloadTexture(const std::string &identifier, SDL_Renderer *renderer)
{
    auto emplaced = texture_cache.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(identifier),
        std::forward_as_tuple(identifier, renderer));
    bool& success = emplaced.second;
    return success;
}
