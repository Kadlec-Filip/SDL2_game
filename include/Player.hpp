#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "Utils.hpp"
#include "DrawableEntity.hpp"

class Player : public DrawableEntity {
public:	
	Player(Vector2f pos, SDL_Texture* texture);
	utils::State getState();
	void setState(utils::State s);
	int isAlive();
	void setDead();
	int getSizeOfStateSprites();
	void setCurrentFrame(int idx);
private:
	bool grounded;
	bool alive = 0;
	utils::State state = utils::State::RUN_R;
	std::map<utils::State, std::vector<SDL_Rect>> state_sprites;
};