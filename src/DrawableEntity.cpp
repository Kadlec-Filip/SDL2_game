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

Vector2f& DrawableEntity::getPos(){ return pos; }
void DrawableEntity::setPos(Vector2f p_pos){ pos = p_pos; }
SDL_Texture* DrawableEntity::getTexture() {return texture; }
SDL_Rect DrawableEntity::getCurrentFrame() {return currentFrame; }
SDL_Rect DrawableEntity::getBoundingBox() {
    SDL_Rect sdlr;
    sdlr.x=pos.x;
    sdlr.y=pos.y;
    sdlr.h=getCurrentFrame().h;
    sdlr.w=getCurrentFrame().w;
    return sdlr;
} 