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

Vector2f Vector2f::operator+(const Vector2f& other_v) const{
    return Vector2f(x + other_v.x, y + other_v.y);
}

Vector2f Vector2f::operator-(const Vector2f& other_v) const {
    return Vector2f(x - other_v.x, y - other_v.y);
}

bool Rectangle::contains(float px, float py) const {
        return (px >= x && px <= x + width && py >= y && py <= y + height);
}

// TODO to recheck when dealing with collision detection
bool Rectangle::intersects(const Rectangle& other) const {
        return !(x > other.x + other.width || x + width < other.x ||
                 y > other.y + other.height || y + height < other.y);
}