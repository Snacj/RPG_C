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
#include "../config.h"
#include "../entity/player.h"
#include "../util/util.h"
#include "../ui/main_menu.h"
#include "../tiles/tiles.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

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
    if (gamePanel.gameState == GAME) {
        playerUpdate(&player);
    }
    return 0;
}

/**
* @brief Draw the game state 
* @param SDL_Renderer* renderer
* @return void
*/
static void draw(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    if (gamePanel.gameState == MAIN_MENU) {
        mainMenuDraw(renderer);
    } else if (gamePanel.gameState == GAME) {
        // load the grass texture
        
        // go over the map and draw the grass texture
        // TODO: draw the map based on the map array
        for(int i = 0; i < MAP_COLS; i++) {
            for (int j = 0; j < MAP_ROWS; j++) {
                SDL_Rect destRect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderCopy(renderer, *(SDL_Texture**)vector_get(&gTextures, MAP[j][i]), NULL, &destRect);
            }
        }
        // load the stone texture
        
        // draw the stone texture
        SDL_RenderCopy(renderer, *(SDL_Texture**)vector_get(&gTextures, 2), NULL, &stoneRect);
        // draw the player
        playerDraw(&player, renderer);
    }
    // render the textures on the Screen
    SDL_RenderPresent(renderer);
}

/**
* @brief The main game loop
* @param SDL_Window* window, SDL_Renderer* renderer
* @return void
*/
void gamePanelLoop(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Event e;
    playerInit(&player);
    init_main_menu(renderer);
    // load the map into array
    readMap("assets/maps/map.txt");
    gamePanel.gameState = MAIN_MENU;
    gamePanel.running = 1;

    while (gamePanel.running) {
        // Set the frame delay
        Uint32 frameStart = SDL_GetTicks();

        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                gamePanel.running = 0;
            }
            switch ( e.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    if (gamePanel.gameState == GAME) gamePanel.gameState = MAIN_MENU;
                    break;
                default:
                    break;
            } 
            if (gamePanel.gameState == MAIN_MENU) {
                handle_main_menu_events(&e);
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

