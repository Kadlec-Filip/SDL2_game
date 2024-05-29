#pragma once // header file WILL NOT get coppied twice
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "Utils.hpp"
#include "DrawableEntity.hpp"
#include "RenderWindow.hpp"

// class RenderWindow;

class DynamicEntity : public DrawableEntity {
public:	
	DynamicEntity(Vector2f pos, SDL_Texture* texture);
	utils::State getState();
	int currentJumpHeight=0;
	void setState(utils::State s);
	int isAlive();
	bool isGrounded();
    void setGrounded();
	void unsetGrounded();
	bool isJumping();
    void setJumping();
	void unsetJumping();
	bool isFalling();
    void setFalling();
	void unsetFalling();
	//void setDead();
	int getSizeOfStateSprites();
	void setCurrentFrame(int idx);
	virtual void setTexture(RenderWindow& w) = 0;
	void updateDynamicEntity(utils::State s, RenderWindow& w);
	bool isDynamicEntityRenderBlocked();
    void setDynamicEntityRenderBlocked();
	void unsetDynamicEntityRenderBlocked();
	int getBlockingTextureLen();
	void setBlockingTextureLen(int p_btl);
	void move();
	void setVelocity(Velocity2f p_velocity);
	void setVelocityX(float x);
	void setVelocityY(float y);
	virtual void setVelocityByState() = 0;
	Velocity2f& getVelocity();

protected:
	bool grounded=false;
	bool jumping=false;
	bool falling=false;
	bool alive = false;
	bool dynamicEntityRenderBlocked=false;
	int blockingTextureLen;
	
	Velocity2f velocity {0,0};
	utils::State state = utils::State::RUN_R;
	std::map<utils::State, std::vector<SDL_Rect>> state_sprites;
};
