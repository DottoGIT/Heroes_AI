/*
 * File:        TextureManager.h
 * Description: Implements a Texture Manager with lazy loading
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        02.12.2024
 */

#pragma once
#include <unordered_map>
#include <string>

#include "Texture.h"


class TextureManager
{
private:
    std::unordered_map<std::string, Texture> texture_cache;
public:
    const Texture& get_texture(const std::string& identifier, SDL_Renderer* renderer);
    bool preloadTexture(const std::string& identifier, SDL_Renderer* renderer);
};