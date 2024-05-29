#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DynamicEntity.hpp"

class Player : public DynamicEntity {
public:
	Player(Vector2f pos, SDL_Texture* texture);
	int isAlive();
	void setDead();
	void setHp(int damage);
	int getHp();
	void setStamina();
	int getStamina();
	//void setTexture(RenderWindow& w) override;
	void setTexture(PlayerTextureLoader& ptl);
	void setVelocityByState() override;

private:
	bool alive = false;
	int hp = 100;
	int stamina = 100;
	// etc

};
