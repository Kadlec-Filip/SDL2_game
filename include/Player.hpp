#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "DrawableEntity.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

class Player : public DrawableEntity {
public:	
	Player(Vector2f pos, std::vector<SDL_Texture*> texs_vec);
	bool jump();
	int isDead();
private:
	bool grounded;
	int dead = 0;
	std::vector<SDL_Texture*> texs_vec;
};