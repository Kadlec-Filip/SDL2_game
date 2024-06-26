#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"
#include "Utils.hpp"

class EventManager{
public:
    EventManager(Player& p_player);
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    void keyboardProcess(PlayerTextureLoader& p_ptl); 
    utils::CollisionMoveType identifyCollisionHorizontal(const SDL_Rect &a, const SDL_Rect &b);
    utils::CollisionMoveType identifyCollisionVertical(const SDL_Rect &a, const SDL_Rect &b);
    bool detectCollision(const SDL_Rect &a, const SDL_Rect &b);
    void keepPlayerInGame();
    void resolveCollision(Player& dynamicEntity, DrawableEntity& staticEntity); // TODO create more generic dynamic(player&npc)+static entities
    void resolveAllCollisions(Player& dynamicEntity, std::vector<DrawableEntity> staticEntities);
    void resolveAllCollisions(std::vector<Player> dynamicEntity, std::vector<DrawableEntity> staticEntities); // TODO
protected:
    Player& player;
};