#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Vector2f{
    Vector2f();
    Vector2f(float x, float y);
    void print();
    float x, y;
};