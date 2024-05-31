#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>

#include "SDLRenderUtils.hpp"
#include "RenderWindow.hpp"

class TextureLoader{
public:
    TextureLoader(RenderWindow& re);
    ~TextureLoader();
    SDL_Texture* getTextureByState(utils::State s);
protected:
    virtual void preLoadTextures() = 0;
    std::map<utils::State, SDL_Texture*> textures;
    RenderWindow& re;
};