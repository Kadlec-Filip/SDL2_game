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

bool EventManager::detectCollision(const SDL_Rect& a, const SDL_Rect& b){
    return SDL_HasIntersection(&a, &b);
}
utils::CollisionMoveType EventManager::identifyCollisionHorizontal(const SDL_Rect& a, const SDL_Rect& b){
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


utils::CollisionMoveType EventManager::identifyCollisionVertical(const SDL_Rect& a, const SDL_Rect& b){
    // (a.y + a.h > b.y && a.y + a.h < b.y + b.h) & (a.y < b.y + b.h && a.y > b.y):
    // conditions above detect collisions in general. introduced stricter check, since if you come to obstacle
    // from LEFT or RIGHT, you may detect BOTTOM/TOP collisions, which results in unwanted move behavior.
    // Reason: Due to GRAVITY, BOTTOM(and top) collision must be always checked first. No strict check is mandatory for Horizontal collisions.
    if (a.y + a.h > b.y && a.y + a.h <= b.y + utils::GRAVITY) {
        // 'a' hit 'b' from the top
        return utils::CollisionMoveType::BOTTOM;
    }
    if (a.y < b.y + b.h && a.y >= b.y + b.h - utils::GRAVITY) {
        // 'a' hit 'b' from the bottom
        return utils::CollisionMoveType::TOP;
    }
    // If all cases are correct, the program shouldnt not reach here
    return utils::CollisionMoveType::NONE;
}

void EventManager::resolveCollision(Player& dynamicEntity, DrawableEntity& staticEntity){
    utils::CollisionMoveType identifiedCollision;
    if(detectCollision(dynamicEntity.getBoundingBox(), staticEntity.getBoundingBox())){
        identifiedCollision = identifyCollisionVertical(dynamicEntity.getBoundingBox(), staticEntity.getBoundingBox());
        if (identifiedCollision == utils::CollisionMoveType::BOTTOM){
            dynamicEntity.setPos(Vector2f {dynamicEntity.getPos().x, staticEntity.getPos().y - (dynamicEntity.getCurrentFrame().h)});
            dynamicEntity.setVelocityY(0);
            dynamicEntity.unsetFalling();
            dynamicEntity.setGrounded();
        }
        else if (identifiedCollision == utils::CollisionMoveType::TOP){
            dynamicEntity.setPos(Vector2f {dynamicEntity.getPos().x, staticEntity.getPos().y + (staticEntity.getCurrentFrame().h)});
            dynamicEntity.unsetJumping();
            dynamicEntity.setFalling();
            dynamicEntity.setVelocityY(utils::GRAVITY);
        }
    }
    if(detectCollision(dynamicEntity.getBoundingBox(), staticEntity.getBoundingBox())){
        identifiedCollision = identifyCollisionHorizontal(dynamicEntity.getBoundingBox(), staticEntity.getBoundingBox());
        if (identifiedCollision == utils::CollisionMoveType::RIGHT){
            dynamicEntity.setPos(Vector2f {staticEntity.getPos().x - (dynamicEntity.getCurrentFrame().w), dynamicEntity.getPos().y});
        }
        else if (identifiedCollision == utils::CollisionMoveType::LEFT){
            dynamicEntity.setPos(Vector2f {staticEntity.getPos().x + (staticEntity.getCurrentFrame().w), dynamicEntity.getPos().y});
        }
    }
}

void EventManager::resolveAllCollisions(Player& dynamicEntity, std::vector<DrawableEntity> staticEntities){ // TODO: vector const ref?
    for (auto se : staticEntities){
        resolveCollision(dynamicEntity, se);
    }
    keepPlayerInGame();
}

void EventManager::keepPlayerInGame(){
    if(player.getPos().x < 1)
        player.setPos(Vector2f {1, player.getPos().y});
    if(player.getPos().x > utils::GAME_WIDTH - player.getCurrentFrame().w)
        player.setPos(Vector2f {static_cast<float>(utils::GAME_WIDTH - player.getCurrentFrame().w), player.getPos().y});
    if(player.getPos().y < 1)
        player.setPos(Vector2f {player.getPos().x, 1});
    if(player.getPos().y > utils::GAME_WINDOW_HEIGHT)
        player.setPos(Vector2f {player.getPos().x, static_cast<float>(utils::GAME_WINDOW_HEIGHT - player.getCurrentFrame().h)});
}
