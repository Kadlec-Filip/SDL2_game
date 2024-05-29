#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Utils.hpp"

namespace sdlRenderUtils{
    // TODO: encapsulate, a lot of similar data abstractions to come
    extern SDL_Rect spriteFrame1;
    extern SDL_Rect spriteFrame2;
    extern SDL_Rect spriteFrame3;
    extern SDL_Rect spriteFrame4;
    extern SDL_Rect spriteFrame5;
    extern SDL_Rect spriteFrame6;
    extern SDL_Rect spriteFrame7;
    extern SDL_Rect spriteFrame8;
    extern SDL_Rect spriteFrame9;
    extern SDL_Rect spriteFrame10;
    extern std::vector<SDL_Rect> playerRunLSpritesheet;
    extern std::vector<SDL_Rect> playerRunRSpritesheet;
    extern std::vector<SDL_Rect> playerIdleSpritesheet;
    extern std::vector<SDL_Rect> playerAttackRSpritesheet;
    extern std::vector<SDL_Rect> playerJumpRSpritesheet;
    extern std::vector<SDL_Rect> playerFallRSpritesheet;
    extern const char* playerTextureRunLPath;  // const char * mandatory for render window
    extern const char* playerTextureRunRPath;
    extern const char* playerTextureIdlePath;
    extern const char* playerTextureAttackRPath;
    extern const char* playerTextureJumpRPath;
    extern const char* playerTextureFalllRPath;
}