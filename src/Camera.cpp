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
    if (p.getPos().x > camRect.x + utils::GAME_WINDOW_WIDTH*3/4){
        camRect.x = p.getPos().x - utils::GAME_WINDOW_WIDTH*1/4;
    }
    else if (p.getPos().x > camRect.x + utils::GAME_WINDOW_WIDTH*1/4){
        camRect.x = p.getPos().x - utils::GAME_WINDOW_WIDTH*3/4;
    }
    //Keep the window in bounds of the game
    // if( camera.x < 0 )
    // { 
    //     camera.x = 0;
    // }
    // if( camera.y < 0 )
    // {
    //     camera.y = 0;
    // }
}