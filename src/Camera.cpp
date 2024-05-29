#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Player.hpp"
#include "Camera.hpp"
#include "Utils.hpp"

Camera::Camera(Player& player) : p(player){
    camRect.x = 0;
    camRect.y = 0;
    camRect.h = utils::GAME_HEIGHT;
    camRect.w = utils::GAME_WIDTH;
}

void Camera::updateCameraPosition(){
    camRect.x = ( p.getPos().x + p.getCurrentFrame().h/2 ) - utils::GAME_WINDOW_WIDTH/2;
    //Keep the window in bounds of the game
    if( camRect.x < 0 )
    { 
        camRect.x = 0;
    }
    if( camRect.x > utils::GAME_WIDTH - utils::GAME_WINDOW_WIDTH)
    { 
        camRect.x = utils::GAME_WIDTH - utils::GAME_WINDOW_WIDTH;
    }
}