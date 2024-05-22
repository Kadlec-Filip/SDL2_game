#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"

class EventManager{
public:
    EventManager(Player& p_player);
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    void keyProcess(RenderWindow& p_rw); 
protected:
    Player& player;
};