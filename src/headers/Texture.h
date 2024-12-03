/*
 * File:        Texture.h
 * Description: Implements a wrapper over SDL_Texture
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        02.12.2024
 */

#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Texture
{
public:
    Texture(const std::string& path, SDL_Renderer* renderer);
    ~Texture();
    SDL_Texture* getTexture() const;
    int get_width() const;
    int get_height() const;
private:
    SDL_Texture* texture_;
    int width_, height_;
};
