#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "Utils.hpp"
#include "DrawableEntity.hpp"
#include "RenderWindow.hpp"

class Player : public DrawableEntity {
public:	
	Player(Vector2f pos, SDL_Texture* texture);
	utils::State getState();
	void setState(utils::State s);
	int isAlive();
	void setDead();
	int getSizeOfStateSprites();
	void setCurrentFrame(int idx);
	void setTexture(utils::State s, RenderWindow& w);
	void updatePlayer(utils::State s, RenderWindow& w);
	bool isPlayerRenderBlocked();
    void setPlayerRenderBlocked();
	void unsetPlayerRenderBlocked();
	int getBlockingTextureLen();
	void setBlockingTextureLen(int p_btl);

private:
	bool grounded;
	bool alive = false;
	bool playerRenderBlocked=false;
	int blockingTextureLen;
	utils::State state = utils::State::RUN_R;
	std::map<utils::State, std::vector<SDL_Rect>> state_sprites;
};
