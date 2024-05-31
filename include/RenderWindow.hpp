#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DrawableEntity.hpp"
#include "Camera.hpp"

class RenderWindow{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    RenderWindow(const char* p_title, int width, int height);
    ~RenderWindow();
    SDL_Texture* LoadTexture(const char* filepath);
    void clear();
    void render(DrawableEntity& dentity);
    void render(DrawableEntity& dentity, Camera& camera);
    void display();
    int getRefreshRate();
};