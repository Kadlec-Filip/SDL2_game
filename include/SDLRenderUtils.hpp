#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Utils.hpp"

namespace sdlRenderUtils{
    // TODO: encapsulate, a lot of similar data abstractions to come
    SDL_Rect spriteFrame1 {40, 40, 40, 40};
    SDL_Rect spriteFrame2 {160, 40, 40, 40};
    SDL_Rect spriteFrame3 {280, 40, 40, 40};
    SDL_Rect spriteFrame4 {400, 40, 40, 40};
    SDL_Rect spriteFrame5 {520, 40, 40, 40};
    SDL_Rect spriteFrame6 {640, 40, 40, 40};
    SDL_Rect spriteFrame7 {760, 40, 40, 40};
    SDL_Rect spriteFrame8 {880, 40, 40, 40};
    SDL_Rect spriteFrame9 {1000, 40, 40, 40};
    SDL_Rect spriteFrame10 {1120, 40, 40, 40};
    std::vector<SDL_Rect> playerRunLSpritesheet {spriteFrame9, spriteFrame8, spriteFrame7, spriteFrame6, spriteFrame5, spriteFrame4, spriteFrame3, spriteFrame2, spriteFrame1};
    std::vector<SDL_Rect> playerRunRSpritesheet {spriteFrame1, spriteFrame2, spriteFrame3, spriteFrame4, spriteFrame5, spriteFrame6, spriteFrame7, spriteFrame8, spriteFrame9};
    std::vector<SDL_Rect> playerIdleSpritesheet {spriteFrame1, spriteFrame2, spriteFrame3, spriteFrame4, spriteFrame5, spriteFrame6, spriteFrame7, spriteFrame8, spriteFrame9, spriteFrame10};
    std::vector<SDL_Rect> playerAttackRSpritesheet {spriteFrame1, spriteFrame2, spriteFrame3, spriteFrame4};
    const char* playerTextureRunLPath = "../res/gfx/_Run_L.png";  // const char * mandatory for render window
    const char* playerTextureRunRPath = "../res/gfx/_Run_R.png";
    const char* playerTextureIdlePath = "../res/gfx/_Idle.png";
    const char* playerTextureAttackRPath = "../res/gfx/_Attack.png";
}