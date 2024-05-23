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

void Player::setTexture(utils::State s, RenderWindow& w){
    switch (s) {
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

void Player::updatePlayer(utils::State s, RenderWindow& w){
    setState(s);
    setTexture(s,w);
}
