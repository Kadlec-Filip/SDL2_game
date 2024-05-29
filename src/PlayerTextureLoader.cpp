#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>

#include "SDLRenderUtils.hpp"
#include "RenderWindow.hpp"
#include "PlayerTextureLoader.hpp"
#include "TextureLoader.hpp"

PlayerTextureLoader::PlayerTextureLoader(RenderWindow& re) : TextureLoader{re} {
    preLoadTextures();
}

void PlayerTextureLoader::preLoadTextures(){
    textures.insert({utils::State::RUN_R, re.LoadTexture(sdlRenderUtils::playerTextureRunRPath)});
    textures.insert({utils::State::RUN_L, re.LoadTexture(sdlRenderUtils::playerTextureRunLPath)});
    textures.insert({utils::State::IDLE, re.LoadTexture(sdlRenderUtils::playerTextureIdlePath)});
    textures.insert({utils::State::ATTACK, re.LoadTexture(sdlRenderUtils::playerTextureAttackRPath)});
    textures.insert({utils::State::FALL, re.LoadTexture(sdlRenderUtils::playerTextureFalllRPath)});
    textures.insert({utils::State::JUMP, re.LoadTexture(sdlRenderUtils::playerTextureJumpRPath)});
}