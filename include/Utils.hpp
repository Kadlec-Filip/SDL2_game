#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace utils{
    inline float hireTimeInSeconds(){
        float t = SDL_GetTicks(); // miliseconds passed during program execution
        t *= 0.001f;
        return t;
    }

    enum class State {RUN_L, RUN_R, IDLE, JUMP, ATTACK, FALL};
    enum class CollisionMoveType {LEFT, RIGHT, TOP, BOTTOM, NONE};
    const int GAME_WINDOW_HEIGHT = 720;
    const int GAME_WINDOW_WIDTH = 1280;
    const int RENDER_SPEED = 10;
    const float PLAYER_RUN_R_VELOCITY = 3;
    const float PLAYER_RUN_L_VELOCITY = -3;
    const float JUMP_VELOCITY = -2;  // Gravity alwas applied -> if jumping JumpVel+GravityVel
    const float JUMP_HEIGHT = 60;
    const float GRAVITY = 1;  // speed for now :)
}