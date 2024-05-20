#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "DrawableEntity.hpp"

RenderWindow::RenderWindow(const char* p_title, int width, int height) : window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
        std::cout << "Window failed to init. ERROR: " << SDL_GetError() << "\n";
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // -1 use the first one that satisfies condition
    // + render as fast as possible (wrt screen)
}
RenderWindow::~RenderWindow(){
    SDL_DestroyWindow(window);
}

SDL_Texture* RenderWindow::LoadTexture(const char* filepath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filepath);

    if (texture == NULL)
        std::cout << "Failed to load texture. ERROR: " << SDL_GetError() << "\n";

    return texture;
}

void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::render(DrawableEntity& dentity){
    SDL_Rect sdl_rectangle_source;
    sdl_rectangle_source.x = dentity.getCurrentFrame().x;
    sdl_rectangle_source.y = dentity.getCurrentFrame().y;
    sdl_rectangle_source.w = dentity.getCurrentFrame().w;
    sdl_rectangle_source.h = dentity.getCurrentFrame().h;

    SDL_Rect sdl_rectangle_dst;
    sdl_rectangle_dst.x = dentity.getPos().x;
    sdl_rectangle_dst.y = dentity.getPos().y;
    sdl_rectangle_dst.w = dentity.getCurrentFrame().w * 4;
    sdl_rectangle_dst.h = dentity.getCurrentFrame().h * 4;
    SDL_RenderCopy(renderer, dentity.getTexture(), &sdl_rectangle_source, &sdl_rectangle_dst);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}

int RenderWindow::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}