#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "EventManager.hpp"

EventManager::EventManager(Player& p_player) : player(p_player) {
    
}

void EventManager::keyboardProcess(RenderWindow& p_rw){
    if (!player.isPlayerRenderBlocked()){
        if (keyboardState[SDL_SCANCODE_J]){
            player.updatePlayer(utils::State::ATTACK, p_rw);
            player.setPlayerRenderBlocked();
            player.setBlockingTextureLen(player.getSizeOfStateSprites());
        }
        else if (keyboardState[SDL_SCANCODE_A]) {
            player.updatePlayer(utils::State::RUN_L, p_rw);
        }
        else if (keyboardState[SDL_SCANCODE_D]){
            player.updatePlayer(utils::State::RUN_R, p_rw);
        }
        else if (keyboardState[SDL_SCANCODE_S]){
            player.updatePlayer(utils::State::IDLE, p_rw);
        }
        else if (keyboardState[SDL_SCANCODE_W]){
            player.updatePlayer(utils::State::IDLE, p_rw);
        }
        else{
            player.updatePlayer(utils::State::IDLE, p_rw);
        }
    }
}