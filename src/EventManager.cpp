#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "EventManager.hpp"

EventManager::EventManager(Player& p_player) : player(p_player) {}

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

bool EventManager::detectCollision(const SDL_Rect& a, const SDL_Rect& b){
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

void EventManager::resolveCollision(Player& dynamicEntity, DrawableEntity& staticEntity){
    if (detectCollision(dynamicEntity.getBoundingBox(), staticEntity.getBoundingBox())){
        // naive initial version -> assume player is above ground and only collision may come between players feet and ground
        player.setPos(Vector2f {dynamicEntity.getPos().x, staticEntity.getPos().y - dynamicEntity.getCurrentFrame().h});  // magic number 4, multiplication of initial version of the ground which will be removed
        player.setVelocityY(0);
        player.setGrounded();
    }
    else{
        player.unsetGrounded();
    }
}

void EventManager::resolveAllCollisions(Player& dynamicEntity, std::vector<DrawableEntity> staticEntities){ // TODO: vector const ref?
    for (auto se : staticEntities){
        resolveCollision(dynamicEntity, se);
    }
}