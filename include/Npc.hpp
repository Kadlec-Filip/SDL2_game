#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DynamicEntity.hpp"

// TBCreated
class Npc : public DynamicEntity {
public:
	Npc(Vector2f pos, SDL_Texture* texture);
	int isAlive();
	void setDead();
	void setHp(int damage);
	int getHp();
	// void setTexture(RenderWindow& w) override;
	// void setVelocityByState() override;

private:
	bool alive = false;
	int hp = 100;
	int stamina = 100;
};
