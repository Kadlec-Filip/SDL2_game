#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "RenderWindow.hpp"
#include "DrawableEntity.hpp"
#include "Math.hpp"
#include "Utils.hpp"

int main(int argc, char* argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed: " << SDL_GetError() << "\n";
    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init has failed: " << SDL_GetError() << "\n";
    
    RenderWindow window("GAME v0.1", 1280, 720);

    SDL_Texture* grassTexture = window.LoadTexture("../res/gfx/ground_grass_1.png");
    // SDL_Texture* grassTexture = window.LoadTexture("../res/gfx/crouchknight.png");

    std::vector<DrawableEntity> dentities_vec = {DrawableEntity(Vector2f((32*4)*0, 720-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*1, 720-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*2, 720-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*3, 720-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*4, 720-(32*4)), grassTexture),
                                                DrawableEntity(Vector2f((32*4)*5, 720-(32*4)), grassTexture)};

    SDL_Event event;
    bool game_running = true;
    const float time_step = 0.01f;  // how much you advance the simulation/game forward with each frame
    float accumulator = 0.0f; // when accumulator == time_step --> update 
    float current_time = utils::hireTimeInSeconds();

    while (game_running){
        int start_ticks = SDL_GetTicks();

        float new_time = utils::hireTimeInSeconds();
        float frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        while (accumulator >= time_step){
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT)
                    game_running = false;
            }
            accumulator -= time_step;
        }

        // const float alpha = accumulator/time_step;

        // Display all drawable entities
        window.clear();
        for (DrawableEntity& dentity : dentities_vec){
            window.render(dentity);
        }
        window.display();

        // regulate the game loop. if loop was faster than refresh rate, sleep for the rest of the refresh time
        int frame_ticks = SDL_GetTicks() - start_ticks;
        if (frame_ticks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frame_ticks);
    }

    SDL_Quit();
    return 0;
}
