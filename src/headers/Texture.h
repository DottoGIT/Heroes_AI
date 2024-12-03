/*
 * File:        Texture.h
 * Description: Implements a wrapper over SDL_Texture
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        02.12.2024
 */

#pragma once
#include <SDL.h>
#include <string>

class Texture
{
private:
    SDL_Texture* texture_;
    int width_, height_;
public:
    Texture(const std::string& path, SDL_Renderer* renderer);
    ~Texture();
    SDL_Texture* getTexture() const;
    int get_width() const;
    int get_height() const;
};
