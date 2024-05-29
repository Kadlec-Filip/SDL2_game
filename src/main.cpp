#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Camera.hpp"
#include "DrawableEntity.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Utils.hpp"
#include "EventManager.hpp"

// TODO:use DrawableEntity as template, inherit StaticEntity (ground etc) from it. Inherit DynamicEntity (NPCs, Player) from it.
//      Remove RenderWindow from Player class; RenderManager(?) could take care of this
//      Move player state logic out of main (is jumping, is falling...)
//      Separate EventManager into multiple classes!
//      Layer the program structure. Circural includes present (Camera+RenderWindow+Player)


int main(int argc, char* argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed: " << SDL_GetError() << "\n";
    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init has failed: " << SDL_GetError() << "\n";
    
    RenderWindow window("GAME v0.1", utils::GAME_WINDOW_WIDTH, utils::GAME_WINDOW_HEIGHT);

    SDL_Texture* grassTexture = window.LoadTexture("../res/gfx/ground_grass_1.png");
    SDL_Texture* playerTexture = window.LoadTexture("../res/gfx/_Idle.png");

    // Player player(Vector2f(utils::GAME_WINDOW_WIDTH/2-(32*2), utils::GAME_WINDOW_HEIGHT/2-(32*2)), playerTexture);
    Player player(Vector2f(utils::GAME_WINDOW_WIDTH/2-(40), utils::GAME_WINDOW_HEIGHT/2-40), playerTexture);

    Camera camera(player);

    // Populate ground 
    std::vector<DrawableEntity> dentities_vec;
    dentities_vec.reserve(100);
    for (int i=0; i<40; ++i){
        dentities_vec.emplace_back(DrawableEntity(Vector2f((32)*i, utils::GAME_WINDOW_HEIGHT-(32)), grassTexture));
    }
    for (int i=5; i<7; ++i){
        dentities_vec.emplace_back(DrawableEntity(Vector2f((32)*i, utils::GAME_WINDOW_HEIGHT-(48)), grassTexture));
    }
    for (int i=10; i<13; ++i){
        dentities_vec.emplace_back(DrawableEntity(Vector2f((32)*i, utils::GAME_WINDOW_HEIGHT-(64)), grassTexture));
    }
    for (int i=13; i<17; ++i){
        dentities_vec.emplace_back(DrawableEntity(Vector2f((32)*i, utils::GAME_WINDOW_HEIGHT-(80)), grassTexture));
    }
    for (int i=20; i<24; ++i){
        dentities_vec.emplace_back(DrawableEntity(Vector2f((32)*i, utils::GAME_WINDOW_HEIGHT-(110)), grassTexture));
    }
    for (int i=27; i<30; ++i){
        dentities_vec.emplace_back(DrawableEntity(Vector2f((32)*i, utils::GAME_WINDOW_HEIGHT-(140)), grassTexture));
    }
    for (int i=34; i<36; ++i){
        dentities_vec.emplace_back(DrawableEntity(Vector2f((32)*i, utils::GAME_WINDOW_HEIGHT-(170)), grassTexture));
    }

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
            else if (player.isPlayerRenderBlocked()){
                player.setBlockingTextureLen(player.getBlockingTextureLen() - 1);
                if (player.getBlockingTextureLen() <= 0){
                    player.unsetPlayerRenderBlocked();
                }
            }
            player.setCurrentFrame(spriteIdx);
        }

        // TODO 
        if (player.isJumping()){
            player.currentJumpHeight -= 1;
            if (player.currentJumpHeight <= 0){
                player.unsetJumping();
                player.setFalling();
                player.updatePlayer(utils::State::FALL, window);
            }
            else{
                player.updatePlayer(utils::State::JUMP, window);
            }
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

        // Resolve collisions
        eventManager.resolveAllCollisions(player, dentities_vec);

        // Move actual game window based on player position
        camera.updateCameraPosition();
        
        // Display all drawable entities
        window.clear();
        for (DrawableEntity& dentity : dentities_vec){
            window.render(dentity, camera);
        }
        window.render(player, camera);
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
