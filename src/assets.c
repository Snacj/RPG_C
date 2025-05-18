/*
*
* Credits for the Assets:
* https://snoblin.itch.io/pixel-rpg-skeleton-free
*
*/

#include "assets.h"
#include "util.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

Vector gTextures;
Vector gPlayerTextures;

static SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer, Vector* vecTextures) {
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

    vector_push_back(vecTextures, &texture);

    return texture;
}

int loadAssets(SDL_Renderer* renderer) {
    vector_init(&gTextures, sizeof(SDL_Texture*));
    vector_init(&gPlayerTextures, sizeof(SDL_Texture*));

    TextureAsset assets[] = {
        { "grass",          "assets/sprites/grass.png"},
        { "plain_grass",    "assets/sprites/testing.png"},
        { "stone",          "assets/sprites/stone.png"},
    };

    size_t numAssets = sizeof(assets) / sizeof(assets[0]);

    for (size_t i = 0; i < numAssets; i++) {
        SDL_Texture *tex = loadTexture(assets[i].path, renderer, &gTextures);
        if (!tex) {
            printf("Failed to load asset: %s\n", assets[i].path);
            return 0;
        }
    }
    TextureAsset playerAssets[] = {
        { "player_down_idle_1",         "assets/sprites/player_down_idle_1.png"},
        { "player_down_idle_2",         "assets/sprites/player_down_idle_2.png"},
        { "player_down_1",              "assets/sprites/player_down_1.png"},
        { "player_down_2",              "assets/sprites/player_down_2.png"},
        { "player_up_idle_1",           "assets/sprites/player_up_idle_1.png"},
        { "player_up_idle_2",           "assets/sprites/player_up_idle_2.png"},
        { "player_up_1",                "assets/sprites/player_up_1.png"},
        { "player_up_2",                "assets/sprites/player_up_2.png"},
        { "player_right_idle_1",        "assets/sprites/player_right_idle_1.png"},
        { "player_right_idle_2",        "assets/sprites/player_right_idle_2.png"},
        { "player_right_1",             "assets/sprites/player_right_1.png"},
        { "player_right_2",             "assets/sprites/player_right_2.png"},
        { "player_left_idle_1",         "assets/sprites/player_left_idle_1.png"},
        { "player_left_idle_2",         "assets/sprites/player_left_idle_2.png"},
        { "player_left_1",              "assets/sprites/player_left_1.png"},
        { "player_left_2",              "assets/sprites/player_left_2.png"},
    };

    size_t numPlayerAssets = sizeof(playerAssets) / sizeof(playerAssets[0]);

    for (size_t i = 0; i < numPlayerAssets; i++) {
        SDL_Texture *tex = loadTexture(playerAssets[i].path, renderer, &gPlayerTextures);
        if (!tex) {
            printf("Failed to load asset: %s\n", playerAssets[i].path);
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

    for (size_t i = 0; i < gPlayerTextures.size; i++) {
        SDL_Texture* texture = *(SDL_Texture**)vector_get(&gPlayerTextures, i);
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    vector_free(&gPlayerTextures);
}

