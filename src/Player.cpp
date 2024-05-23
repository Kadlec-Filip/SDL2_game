#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Utils.hpp"
#include "SDLRenderUtils.hpp"

Player::Player(Vector2f pos, SDL_Texture* texture) : DrawableEntity{pos, texture} {
    currentFrame = sdlRenderUtils::spriteFrame1;
    state_sprites.insert({utils::State::RUN_R, sdlRenderUtils::playerRunRSpritesheet});
    state_sprites.insert({utils::State::RUN_L, sdlRenderUtils::playerRunLSpritesheet});
    state_sprites.insert({utils::State::IDLE, sdlRenderUtils::playerIdleSpritesheet});
    state_sprites.insert({utils::State::ATTACK, sdlRenderUtils::playerAttackRSpritesheet});
}

utils::State Player::getState(){ return state; }
void Player::setState(utils::State s){ state = s; }

int Player::getSizeOfStateSprites(){
    std::vector<SDL_Rect> currentSpriteFrameVec = state_sprites.at(getState());
    return currentSpriteFrameVec.size();
}

void Player::setCurrentFrame(int idx){
    std::vector<SDL_Rect> currentSpriteFrameVec = state_sprites.at(getState());
    currentFrame = currentSpriteFrameVec.at(idx);
}

bool Player::isPlayerRenderBlocked(){ return playerRenderBlocked; }

void Player::setPlayerRenderBlocked() { playerRenderBlocked=true; }
void Player::unsetPlayerRenderBlocked() {playerRenderBlocked=false; }

int Player::getBlockingTextureLen() { return blockingTextureLen; }
void Player::setBlockingTextureLen(int p_btl) {blockingTextureLen = p_btl; }

void Player::setTexture(RenderWindow& w){
    switch (state) {
    case utils::State::RUN_R:
        texture = w.LoadTexture(sdlRenderUtils::playerTextureRunRPath);
        break;
    case utils::State::RUN_L:
        texture = w.LoadTexture(sdlRenderUtils::playerTextureRunLPath);
        break;
    case utils::State::IDLE:
        texture = w.LoadTexture(sdlRenderUtils::playerTextureIdlePath);
        break;
    case utils::State::ATTACK:
        texture = w.LoadTexture(sdlRenderUtils::playerTextureAttackRPath);
        break;
    default:
        texture = w.LoadTexture(sdlRenderUtils::playerTextureIdlePath);
        break;
    }
}

void Player::setVelocity(Velocity2f p_velocity){ velocity = p_velocity; }

void Player::setVelocityByState(){
    switch (state) {
    case utils::State::RUN_R:
        velocity.value.x = utils::PLAYER_RUN_R_VELOCITY;
        break;
    case utils::State::RUN_L:
        velocity.value.x = utils::PLAYER_RUN_L_VELOCITY;
        break;
    case utils::State::IDLE:
        velocity.value.x = 0;
        break;
    case utils::State::ATTACK: // TODO if prev state is runR -> speed from runR, if leftR..
        velocity.value.x = 0;
        break;
    default:
        velocity.value.x = 0;
        break;
    }

    if (!isGrounded()) {
        velocity.value.y = utils::GRAVITY; // Apply gravity
    }
}

void Player::move(){
    pos.x += velocity.value.x;
    pos.y += velocity.value.y;
}

void Player::updatePlayer(utils::State s, RenderWindow& w){
    setState(s);
    setTexture(w);
    setVelocityByState(); // TODO rename (updateVelicities?)
}

Velocity2f& Player::getVelocity(){ return velocity; }
void Player::setVelocityX(float x){
    velocity.value.x = x;
}
void Player::setVelocityY(float y){
    velocity.value.y = y;
}

bool Player::isGrounded(){ return grounded; }
void Player::setGrounded() { grounded = true; }
void Player::unsetGrounded() { grounded = false; }