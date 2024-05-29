#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>

#include "TextureLoader.hpp"
#include "RenderWindow.hpp"

class PlayerTextureLoader : public TextureLoader{
public:
    PlayerTextureLoader(RenderWindow& re);
private:
    void preLoadTextures() override;
};