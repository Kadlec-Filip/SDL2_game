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
    utils::State playerRunState = utils::State::RUN_R;
    std::vector<SDL_Rect> playerRunSpritesheet {spriteFrame1, spriteFrame2, spriteFrame3, spriteFrame4, spriteFrame5, spriteFrame6, spriteFrame7, spriteFrame8, spriteFrame9};
    std::vector<SDL_Rect> spriteFrameVec = sdlRenderUtils::playerRunSpritesheet;
}