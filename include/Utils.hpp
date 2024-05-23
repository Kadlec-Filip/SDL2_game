#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace utils{
    inline float hireTimeInSeconds(){
        float t = SDL_GetTicks(); // miliseconds passed during program execution
        t *= 0.001f;
        return t;
    }

    enum class State {RUN_L, RUN_R, IDLE, JUMP, ATTACK};
    const int GAME_WINDOW_HEIGHT = 720;
    const int GAME_WINDOW_WIDTH = 1280;
    const int RENDER_SPEED = 10;
    const float PLAYER_RUN_R_VELOCITY = 5;
    const float PLAYER_RUN_L_VELOCITY = -5;
    const float JUMP_VELOCITY = 1;
    const float GRAVITY = 1;  // speed for now :)
}