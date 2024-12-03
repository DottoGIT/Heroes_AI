#include "Texture.h"
#include <SDL_image.h>
#include <stdexcept>
#include <format>

Texture::Texture(const std::string &path, SDL_Renderer* renderer)
{
    texture_ = IMG_LoadTexture(renderer, path.c_str());
    if (!texture_)
        throw std::runtime_error("Error! Couldn't load a texture! SDL Error:\n" + std::string(SDL_GetError()));
    if (SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_)) {
        SDL_DestroyTexture(texture_);
        throw std::runtime_error("Error! Couldn't query texture! Texture discarded! SDL Error:\n" + std::string(SDL_GetError()));
    }
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture_);
}

SDL_Texture *Texture::getTexture() const
{
    return texture_;
}

int Texture::get_width() const
{
    return width_;
}

int Texture::get_height() const
{
    return height_;
}