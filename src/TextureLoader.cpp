#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>

#include "SDLRenderUtils.hpp"
#include "RenderWindow.hpp"
#include "TextureLoader.hpp"

TextureLoader::TextureLoader(RenderWindow& re_p) : re(re_p) {}

TextureLoader::~TextureLoader(){
    for (auto& texMapElem : textures){
        if (texMapElem.second != nullptr){
            SDL_DestroyTexture(texMapElem.second);
        }
    }
    textures.clear();
}

SDL_Texture* TextureLoader::getTextureByState(utils::State s){ return textures.at(s); }