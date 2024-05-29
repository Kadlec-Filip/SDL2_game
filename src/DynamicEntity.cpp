#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "DynamicEntity.hpp"
#include "Utils.hpp"
#include "SDLRenderUtils.hpp"

DynamicEntity::DynamicEntity(Vector2f pos, SDL_Texture* texture) : DrawableEntity{pos, texture} {
    // currentFrame = sdlRenderUtils::spriteFrame1;
    // state_sprites.insert({utils::State::RUN_R, sdlRenderUtils::playerRunRSpritesheet});
    // state_sprites.insert({utils::State::RUN_L, sdlRenderUtils::playerRunLSpritesheet});
    // state_sprites.insert({utils::State::IDLE, sdlRenderUtils::playerIdleSpritesheet});
    // state_sprites.insert({utils::State::ATTACK, sdlRenderUtils::playerAttackRSpritesheet});
    // state_sprites.insert({utils::State::JUMP, sdlRenderUtils::playerJumpRSpritesheet});
    // state_sprites.insert({utils::State::FALL, sdlRenderUtils::playerFallRSpritesheet});
}

utils::State DynamicEntity::getState(){ return state; }
void DynamicEntity::setState(utils::State s){ state = s; }

int DynamicEntity::getSizeOfStateSprites(){
    std::vector<SDL_Rect> currentSpriteFrameVec = state_sprites.at(getState());
    return currentSpriteFrameVec.size();
}

void DynamicEntity::setCurrentFrame(int idx){
    std::vector<SDL_Rect> currentSpriteFrameVec = state_sprites.at(getState());
    currentFrame = currentSpriteFrameVec.at(idx);
}

bool DynamicEntity::isDynamicEntityRenderBlocked(){ return dynamicEntityRenderBlocked; }

void DynamicEntity::setDynamicEntityRenderBlocked() { dynamicEntityRenderBlocked=true; }
void DynamicEntity::unsetDynamicEntityRenderBlocked() {dynamicEntityRenderBlocked=false; }

int DynamicEntity::getBlockingTextureLen() { return blockingTextureLen; }
void DynamicEntity::setBlockingTextureLen(int p_btl) {blockingTextureLen = p_btl; }

void DynamicEntity::setVelocity(Velocity2f p_velocity){ velocity = p_velocity; }

void DynamicEntity::move(){
    pos.x += velocity.value.x;
    pos.y += velocity.value.y;
}

void DynamicEntity::updateDynamicEntity(utils::State s, RenderWindow& w){
    setState(s);
    if (s == utils::State::JUMP || s == utils::State::FALL){
        unsetGrounded();
    }
    setTexture(w);
    setVelocityByState(); // TODO rename (updateVelicities?)
}

Velocity2f& DynamicEntity::getVelocity(){ return velocity; }
void DynamicEntity::setVelocityX(float x){
    velocity.value.x = x;
}
void DynamicEntity::setVelocityY(float y){
    velocity.value.y = y;
}

bool DynamicEntity::isGrounded(){ return grounded; }
void DynamicEntity::setGrounded() { grounded = true; }
void DynamicEntity::unsetGrounded() { grounded = false; }

bool DynamicEntity::isJumping(){ return jumping; }
void DynamicEntity::setJumping() { jumping = true; }
void DynamicEntity::unsetJumping() { jumping = false; }

bool DynamicEntity::isFalling() { return falling; }
void DynamicEntity::setFalling() { falling = true; }
void DynamicEntity::unsetFalling() { falling = false; }