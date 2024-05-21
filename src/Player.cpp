#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Utils.hpp"
#include "SDLRenderUtils.hpp"
#include "DrawableEntity.hpp"

Player::Player(Vector2f pos, SDL_Texture* texture) : DrawableEntity{pos, texture} {
    currentFrame = sdlRenderUtils::spriteFrame1;
    state_sprites.insert({sdlRenderUtils::playerRunState, sdlRenderUtils::playerRunSpritesheet}); 
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