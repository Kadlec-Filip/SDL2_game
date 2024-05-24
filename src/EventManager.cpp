#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "EventManager.hpp"

EventManager::EventManager(Player& p_player) : player(p_player) {}

void EventManager::keyboardProcess(RenderWindow& p_rw){
    if (!player.isPlayerRenderBlocked() && !player.isJumping() && !player.isFalling()){
        if (keyboardState[SDL_SCANCODE_J]){
            player.updatePlayer(utils::State::ATTACK, p_rw);
            player.setPlayerRenderBlocked();
            player.setBlockingTextureLen(player.getSizeOfStateSprites());
        }
        else if (keyboardState[SDL_SCANCODE_SPACE]){
            player.updatePlayer(utils::State::JUMP, p_rw);
            player.setJumping();
            player.currentJumpHeight = utils::JUMP_HEIGHT;
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

utils::CollisionMoveType EventManager::detectCollision(const SDL_Rect& a, const SDL_Rect& b){
    // check manually for collision differentiation
    // for is-player-hit, is-npc-hit etc, use built-in SDL function (return SDL_HasIntersection(&a, &b);)
    if (a.x + a.w <= b.x ||    // 'a' is to the left of 'b'
        b.x + b.w <= a.x ||    // 'b' is to the left of 'a'
        a.y + a.h <= b.y ||    // 'a' is above 'b'
        b.y + b.h <= a.y) {    // 'b' is above 'a'
        return utils::CollisionMoveType::NONE;
    }
    // HERE we know a collision happen, now differentiate between them:
    // ! order important
    if (a.y + a.h > b.y && a.y + a.h < b.y + b.h) {
        // 'a' hit 'b' from the top
        return utils::CollisionMoveType::BOTTOM;
    }
    if (a.y < b.y + b.h && a.y > b.y) {
        // 'a' hit 'b' from the bottom
        return utils::CollisionMoveType::TOP;
    }
    if(a.x + a.w > b.x && a.x + a.w < b.x + b.w){
        // 'a' hit 'b' from the left
        return utils::CollisionMoveType::RIGHT;
    }
    if(a.x < b.x + b.w && a.x > b.x){
        // 'a' hit 'b' from the right
        return utils::CollisionMoveType::LEFT;
    }
    // If all cases are correct, the program shouldnt not reach here
    return utils::CollisionMoveType::NONE;
}

void EventManager::resolveCollision(Player& dynamicEntity, DrawableEntity& staticEntity){
    utils::CollisionMoveType detectedCollision = detectCollision(dynamicEntity.getBoundingBox(), staticEntity.getBoundingBox());
    if (detectedCollision == utils::CollisionMoveType::RIGHT){
        player.setPos(Vector2f {staticEntity.getPos().x - dynamicEntity.getCurrentFrame().w, dynamicEntity.getPos().y});
    }
    else if (detectedCollision == utils::CollisionMoveType::LEFT){
        player.setPos(Vector2f {staticEntity.getPos().x + staticEntity.getCurrentFrame().w, dynamicEntity.getPos().y});
    }
    else if (detectedCollision == utils::CollisionMoveType::BOTTOM){
        player.setPos(Vector2f {dynamicEntity.getPos().x, staticEntity.getPos().y - dynamicEntity.getCurrentFrame().h});
        player.setVelocityY(0);
        player.unsetFalling();
        player.setGrounded();
    }
    else if (detectedCollision == utils::CollisionMoveType::TOP){
        player.setPos(Vector2f {dynamicEntity.getPos().x, staticEntity.getPos().y + staticEntity.getCurrentFrame().h});
        player.unsetJumping();
        player.setFalling();
        player.setVelocityY(utils::GRAVITY);
    }
}

void EventManager::resolveAllCollisions(Player& dynamicEntity, std::vector<DrawableEntity> staticEntities){ // TODO: vector const ref?
    for (auto se : staticEntities){
        resolveCollision(dynamicEntity, se);
    }
}