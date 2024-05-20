#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace utils{
    inline float hireTimeInSeconds(){
        float t = SDL_GetTicks(); // miliseconds passed during program execution
        t *= 0.001f;
        return t;
    }
}