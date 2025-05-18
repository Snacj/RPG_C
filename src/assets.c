#include "assets.h"
#include "util.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture* gTexture = NULL;
SDL_Texture* gPlainGrassTexture = NULL;
SDL_Texture* gPlayerTexture = NULL;

Vector gTextures;

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

    if (!texture) {
        printf("Failed to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        return NULL;
    }

    vector_push_back(&gTextures, &texture);

    return texture;
}

int loadAssets(SDL_Renderer* renderer) {
    vector_init(&gTextures, sizeof(SDL_Texture*));

    TextureAsset assets[] = {
        { "grass",       "assets/sprites/grass.png"},
        { "plain_grass", "assets/sprites/testing.png"},
        { "stone",      "assets/sprites/stone.png"},
        { "player",      "assets/sprites/player.png"},
    };

    size_t numAssets = sizeof(assets) / sizeof(assets[0]);

    for (size_t i = 0; i < numAssets; i++) {
        SDL_Texture *tex = loadTexture(assets[i].path, renderer);
        if (!tex) {
            printf("Failed to load asset: %s\n", assets[i].path);
            return 0;
        }
    }

    return 1;
}


void freeAssets() {
    for (size_t i = 0; i < gTextures.size; i++) {
        SDL_Texture* texture = *(SDL_Texture**)vector_get(&gTextures, i);
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    vector_free(&gTextures);
}

