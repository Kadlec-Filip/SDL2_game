#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DrawableEntity.hpp"
#include "Player.hpp"

class Camera{
private:
    Player& p; // make const
public:
    Camera(Player& p);
    void updateCameraPosition();
    SDL_Rect camRect;
};