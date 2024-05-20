#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "DrawableEntity.hpp"
#include "Math.hpp"

void Vector2f::print(){
    std::cout << "x:" << x << " ; y:" << y << "\n";
}

Vector2f::Vector2f() : x(0.0f), y(0.0f) {}
Vector2f::Vector2f(float x, float y) : x(x), y(y) {}