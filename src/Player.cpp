#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Player.hpp"
#include "DynamicEntity.hpp"
#include "SDLRenderUtils.hpp"

Player::Player(Vector2f pos, SDL_Texture* texture) : DynamicEntity{pos, texture} {
    currentFrame = sdlRenderUtils::spriteFrame1;
    state_sprites.insert({utils::State::RUN_R, sdlRenderUtils::playerRunRSpritesheet});
    state_sprites.insert({utils::State::RUN_L, sdlRenderUtils::playerRunLSpritesheet});
    state_sprites.insert({utils::State::IDLE, sdlRenderUtils::playerIdleSpritesheet});
    state_sprites.insert({utils::State::ATTACK, sdlRenderUtils::playerAttackRSpritesheet});
    state_sprites.insert({utils::State::JUMP, sdlRenderUtils::playerJumpRSpritesheet});
    state_sprites.insert({utils::State::FALL, sdlRenderUtils::playerFallRSpritesheet});
    state_sprites.insert({utils::State::FALL_ATTACK, sdlRenderUtils::playerAttackRSpritesheet});
    state_sprites.insert({utils::State::JUMP_ATTACK, sdlRenderUtils::playerAttackRSpritesheet});
}

void Player::setVelocityByState(){
    velocity.value.y = 0;
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
    // when attacking, dont change movement speed
    case utils::State::ATTACK:
    case utils::State::JUMP_ATTACK:
    // velocity.value.y += 0 // If falling, dont change X, Y=gravity
    case utils::State::FALL:
    case utils::State::FALL_ATTACK:
        break;
    case utils::State::JUMP:
        velocity.value.y += utils::JUMP_VELOCITY;
        break;
    default:
        velocity.value.x = 0;
        velocity.value.y = 0;
        break;
    }

    velocity.value.y += utils::GRAVITY; // Apply gravity
}

void Player::setTexture(PlayerTextureLoader& ptl){
    switch (state) {
    case utils::State::RUN_R:
        texture = ptl.getTextureByState(utils::State::RUN_R);
        break;
    case utils::State::RUN_L:
        texture = ptl.getTextureByState(utils::State::RUN_L);
        break;
    case utils::State::IDLE:
        texture = ptl.getTextureByState(utils::State::IDLE);
        break;
    case utils::State::ATTACK:
    case utils::State::JUMP_ATTACK:
    case utils::State::FALL_ATTACK:
        texture = ptl.getTextureByState(utils::State::ATTACK);
        break;
    case utils::State::JUMP:
        texture = ptl.getTextureByState(utils::State::JUMP);
        break;
    case utils::State::FALL:
        texture = ptl.getTextureByState(utils::State::FALL);
        break;
    default:
        texture = ptl.getTextureByState(utils::State::RUN_R);
        break;
    }
}

// void Player::setTexture(RenderWindow& w){
//     switch (state) {
//     case utils::State::RUN_R:
//         texture = w.LoadTexture(sdlRenderUtils::playerTextureRunRPath);
//         break;
//     case utils::State::RUN_L:
//         texture = w.LoadTexture(sdlRenderUtils::playerTextureRunLPath);
//         break;
//     case utils::State::IDLE:
//         texture = w.LoadTexture(sdlRenderUtils::playerTextureIdlePath);
//         break;
//     case utils::State::ATTACK:
//         texture = w.LoadTexture(sdlRenderUtils::playerTextureAttackRPath);
//         break;
//     case utils::State::JUMP:
//         texture = w.LoadTexture(sdlRenderUtils::playerTextureJumpRPath);
//         break;
//     case utils::State::FALL:
//         texture = w.LoadTexture(sdlRenderUtils::playerTextureFalllRPath);
//         break;
//     default:
//         texture = w.LoadTexture(sdlRenderUtils::playerTextureIdlePath);
//         break;
//     }
// }

int Player::isAlive(){ return alive; }
void Player::setDead() { alive = false; }
void Player::setHp(int damage) { hp -= damage; }
int Player::getHp() { return hp; }