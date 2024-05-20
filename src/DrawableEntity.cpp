#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "DrawableEntity.hpp"

DrawableEntity::DrawableEntity(Vector2f pos, SDL_Texture* texture) : pos(pos), texture(texture) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}
std::vector<SDL_Texture*> tex;



Vector2f& DrawableEntity::getPos(){ return pos; }
SDL_Texture* DrawableEntity::getTexture() {return texture; }
SDL_Rect DrawableEntity::getCurrentFrame() {return currentFrame; } 