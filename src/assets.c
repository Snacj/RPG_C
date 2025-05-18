#include "assets.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture* gTexture = NULL;
SDL_Texture* gPlainGrassTexture = NULL;
SDL_Texture* gPlayerTexture = NULL;

static SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
    return texture;
}

int loadAssets(SDL_Renderer* renderer) {
    gTexture = loadTexture("assets/sprites/grass.png", renderer);
    gPlainGrassTexture = loadTexture("assets/sprites/testing.png", renderer);
    gPlayerTexture = loadTexture("assets/sprites/player.png", renderer);
    if (!gTexture || !gPlainGrassTexture) {
        printf("Failed to load texture image!\n");
        return 0;
    }
    return 1;
}

void freeAssets() {
    if (gTexture) {
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
    }

    if (gPlainGrassTexture) {
        SDL_DestroyTexture(gPlainGrassTexture);
        gPlainGrassTexture = NULL;
    }

    if (gPlayerTexture) {
        SDL_DestroyTexture(gPlayerTexture);
        gPlayerTexture = NULL;
    }
}

