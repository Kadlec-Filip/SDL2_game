#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

struct Vector2f{
    Vector2f();
    Vector2f(float x, float y);
    void print();
    float x, y;
    
    Vector2f operator+(const Vector2f& other_v) const {
        return Vector2f(x + other_v.x, y + other_v.y);
    }

    Vector2f operator-(const Vector2f& other_v) const {
        return Vector2f(x - other_v.x, y - other_v.y);
    }
};

struct Velocity2f {
    Vector2f value;

    Velocity2f() : value() {}
    Velocity2f(float x, float y) : value(x, y) {}
    Velocity2f(Vector2f vec) : value(vec) {}
};

struct Rectangle {
    float x, y; // Position of the top-left corner
    float width, height; // Dimensions of the rectangle

    Rectangle() : x(0), y(0), width(0), height(0) {}
    Rectangle(float x, float y, float width, float height) 
        : x(x), y(y), width(width), height(height) {}

    bool contains(float px, float py) const;
    bool intersects(const Rectangle& other) const;
};


