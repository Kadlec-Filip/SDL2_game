#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Camera{
public:
    Camera();
    void updateCameraPosition(const SDL_Rect& r);
    SDL_Rect camRect;
};