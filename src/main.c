#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include "assets.h"
#include "gamepanel.h"
#include "config.h"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int init_game() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return EXIT_SUCCESS;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!\n");
    }

    gWindow = SDL_CreateWindow("2D Game",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (!gWindow) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return EXIT_SUCCESS;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return EXIT_SUCCESS;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

void close_game() {
    freeAssets();

    if (gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }

    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init_game()) {
        printf("Failed to initialize!\n");
        return EXIT_FAILURE;
    }

    if (!loadAssets(gRenderer)) {
        printf("Failed to load media!\n");
        close_game();
        return EXIT_FAILURE;
    }

    gamePanelLoop(gWindow, gRenderer);

    close_game();
    return EXIT_SUCCESS;
}

