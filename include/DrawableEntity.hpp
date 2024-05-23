#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class DrawableEntity{
public:
    DrawableEntity(Vector2f pos, SDL_Texture* texture);
    Vector2f& getPos();
    void setPos(Vector2f p_pos);
    SDL_Texture* getTexture();
    SDL_Rect getCurrentFrame(); // TODO return ref?
    SDL_Rect getBoundingBox();
protected:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture* texture;
};