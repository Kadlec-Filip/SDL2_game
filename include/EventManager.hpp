#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"

class EventManager{
public:
    EventManager(Player& p_player);
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    void keyboardProcess(RenderWindow& p_rw); 
    bool detectCollision(const SDL_Rect &a, const SDL_Rect &b);
    void resolveCollision(Player& dynamicEntity, DrawableEntity& staticEntity); // TODO create more generic dynamic(player&npc)+static entities
    void resolveAllCollisions(Player& dynamicEntity, std::vector<DrawableEntity> staticEntities);
    void resolveAllCollisions(std::vector<Player> dynamicEntity, std::vector<DrawableEntity> staticEntities); // TODO
protected:
    Player& player;
};