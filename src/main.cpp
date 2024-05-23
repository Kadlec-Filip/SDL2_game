#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "DrawableEntity.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "EventManager.hpp"

// TODO:use DrawableEntity as template, inherit StaticEntity (ground etc) from it. Inherit DynamicEntity (NPCs, Player) from it.
//      Remove RenderWindow from Player class; RenderManager(?) could take care of this
//      Separate logic in updating of player object ( render and movement updates shouldn't be tied)
//      2) Ground player object
//      1) Collision detection (first just basic wall, ground)

int main(int argc, char* argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed: " << SDL_GetError() << "\n";
    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init has failed: " << SDL_GetError() << "\n";
    
    RenderWindow window("GAME v0.1", utils::GAME_WINDOW_WIDTH, utils::GAME_WINDOW_HEIGHT);

    SDL_Texture* grassTexture = window.LoadTexture("../res/gfx/ground_grass_1.png");
    SDL_Texture* playerTexture = window.LoadTexture("../res/gfx/_Idle.png");

    Player player(Vector2f(utils::GAME_WINDOW_WIDTH/2-(32*2), utils::GAME_WINDOW_HEIGHT/2-(32*2)), playerTexture);
    std::vector<DrawableEntity> dentities_vec = {DrawableEntity(Vector2f((32*4)*0, utils::GAME_WINDOW_HEIGHT-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*1, utils::GAME_WINDOW_HEIGHT-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*2, utils::GAME_WINDOW_HEIGHT-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*3, utils::GAME_WINDOW_HEIGHT-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*4, utils::GAME_WINDOW_HEIGHT-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*5, utils::GAME_WINDOW_HEIGHT-(32*4)), grassTexture)};

    SDL_Event event;
    EventManager eventManager(player);
    bool game_running = true;
    const float time_step = 0.01f;  // how much you advance the simulation/game forward with each frame
    float accumulator = 0.0f; // when accumulator == time_step --> update 
    float current_time = utils::hireTimeInSeconds();
    int spriteCounter = 0;
    int spriteIdx = 0;

    while (game_running){
        int start_ticks = SDL_GetTicks();
        float new_time = utils::hireTimeInSeconds();
        float frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        // Every X cycles update current frame on each obj from their respective sprite sheets
        if (spriteCounter%utils::RENDER_SPEED==0){
            spriteIdx++;
            // if at the end of sprite sheet, set to first frame of sprite sheet
            if (spriteIdx >= player.getSizeOfStateSprites()){
                spriteIdx = spriteCounter = 0;
            }

            // handle blocking animation (e.g. attack)  TODO: to function/object
            if (player.isPlayerRenderBlocked()){
                player.setBlockingTextureLen(player.getBlockingTextureLen() - 1);
                if (player.getBlockingTextureLen() <= 0){
                    player.unsetPlayerRenderBlocked();
                    player.updatePlayer(utils::State::IDLE, window);
                }
            }
            player.setCurrentFrame(spriteIdx);
        }

        while (accumulator >= time_step){
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT)
                    game_running = false;
            }
            accumulator -= time_step;
        }

        eventManager.keyboardProcess(window);

        // Update positions of objects
        player.move();
        // const float alpha = accumulator/time_step;

        // Display all drawable entities
        window.clear();
        for (DrawableEntity& dentity : dentities_vec){
            window.render(dentity);
        }
        window.render(player);
        window.display();

        // regulate the game loop. if loop was faster than refresh rate, sleep for the rest of the refresh time
        int frame_ticks = SDL_GetTicks() - start_ticks;
        if (frame_ticks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frame_ticks);

        spriteCounter++;
    }

    SDL_Quit();
    return 0;
}
