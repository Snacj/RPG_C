/*
* gamepanel.c
*
* This is the GamePanel for the game.
* It handles the main game loop, drawing and updating
* through 3 functions:
* - update: updates the game state
* - draw: draws the game state
* - gamePanelLoop: the main game loop
*
*
*/
#include "gamepanel.h"
#include "assets.h"
#include "config.h"
#include "player.h"
#include "util.h"

Player player;

// This is just for testing Collisions between player and another object
SDL_Rect stoneRect = { 10*TILE_SIZE, 10*TILE_SIZE, TILE_SIZE, TILE_SIZE };

/**
* @brief Update the game state
* @param void
* @return int
*/
static int update(void) {
    // update the player
    playerUpdate(&player);
    return 0;
}

/**
* @brief Draw the game state 
* @param SDL_Renderer* renderer
* @return void
*/
static void draw(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    // load the grass texture
    SDL_Texture* texture = *(SDL_Texture**)vector_get(&gTextures, 0);
    // go over the map and draw the grass texture
    for(int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            SDL_Rect destRect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(renderer, texture, NULL, &destRect);
        }
    }
    // load the stone texture
    texture = *(SDL_Texture**)vector_get(&gTextures, 2);
    // draw the stone texture
    SDL_RenderCopy(renderer, texture, NULL, &stoneRect);
    // draw the player
    playerDraw(&player, renderer);
    // render the textures on the Screen
    SDL_RenderPresent(renderer);
}

/**
* @brief The main game loop
* @param SDL_Window* window, SDL_Renderer* renderer
* @return void
*/
void gamePanelLoop(SDL_Window* window, SDL_Renderer* renderer) {
    int quit = 0;
    SDL_Event e;
    playerInit(&player);

    while (!quit) {
        // Set the frame delay
        Uint32 frameStart = SDL_GetTicks();

        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = 1;
            } 
        }
        // Update the game state
        update();
        // Draw the game state
        draw(renderer);

        // This sets the frame rate to 60 FPS
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAMEDELAY) {
            SDL_Delay(FRAMEDELAY - frameTime);
        }
    }
}

