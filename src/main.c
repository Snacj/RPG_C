/*
 * main.c
 *
 * This file is the main entry point for the game.
 *
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include "main_src/assets.h"
#include "main_src/gamepanel.h"
#include "config.h"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

/**
* @brief initialize the game
* @param void
* @return int
*/
int init_game() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return EXIT_SUCCESS;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest")) {
        printf("Warning: Linear texture filtering not enabled!\n");
    }

    // Create window, set the size and position and Title
    gWindow = SDL_CreateWindow("2D Game",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (!gWindow) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return EXIT_SUCCESS;
    }

    // Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return EXIT_SUCCESS;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

/**
* @brief close the game
* @param void
* @return void
*/
void close_game() {
    // Free loaded images
    freeAssets();

    // Free the renderer
    if (gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }

    // Free the window
    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

/**
* @brief main function
* @param int argc, char* args[]
* @return void
*/
int main(int argc, char* args[]) {
    // Initialize the game
    if (!init_game()) {
        printf("Failed to initialize!\n");
        return EXIT_FAILURE;
    }

    // Load assets
    if (!loadAssets(gRenderer)) {
        printf("Failed to load media!\n");
        close_game();
        return EXIT_FAILURE;
    }

    // start the game loop
    gamePanelLoop(gWindow, gRenderer);

    close_game();
    return EXIT_SUCCESS;
}

