#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Npc.hpp"
#include "DynamicEntity.hpp"
#include "SDLRenderUtils.hpp"

Npc::Npc(Vector2f pos, SDL_Texture* texture) : DynamicEntity{pos, texture} {
    // define NPC stuff
    // currentFrame = sdlRenderUtils::someSpriteSheetForNpc;
    // state_sprites.insert({utils::State::RUN_R, sdlRenderUtils::npcRunRSpritesheet});
}


int Npc::isAlive(){ return alive; }
void Npc::setDead() { alive = false; }
void Npc::setHp(int damage) { hp -= damage; }
int Npc::getHp() { return hp; }