/*
* assets.c
*
* Credits for the Assets:
* https://snoblin.itch.io/pixel-rpg-skeleton-free
*
*/

#include "assets.h"
#include "../util/util.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

Vector gTextures;
Vector gPlayerTextures;

/**
* @brief load a texture from a file
* @param const char* path, SDL_Renderer* renderer, Vector* vecTextures
* @return SDL_Texture*
*/
static SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer, Vector* vecTextures) {
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    }
    // Create texture from surface pixels
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }
    // Get rid of the old loaded surface
    SDL_FreeSurface(loadedSurface);

    if (!texture) {
        printf("Failed to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        return NULL;
    }

    // Add the texture to the vector
    vector_push_back(vecTextures, &texture);

    // return the texture
    return texture;
}

/**
* @brief load all the assets
* @param SDL_Renderer* renderer
* @return int
*/
int loadAssets(SDL_Renderer* renderer) {
    // Initialize the vectors
    vector_init(&gTextures, sizeof(SDL_Texture*));
    vector_init(&gPlayerTextures, sizeof(SDL_Texture*));

    // Name and path of the assets
    TextureAsset assets[] = {
        { "grass",          "assets/sprites/grass.png"},
        { "plain_grass",    "assets/sprites/testing.png"},
        { "stone",          "assets/sprites/stone.png"},
        { "background",          "assets/sprites/background.png"},
        { "start_game_button",          "assets/sprites/start_game_button.png"},
        { "quit_game_button",          "assets/sprites/quit_game_button.png"},
    };

    // Array size
    size_t numAssets = sizeof(assets) / sizeof(assets[0]);

    // Load the assets from the array
    for (size_t i = 0; i < numAssets; i++) {
        SDL_Texture *tex = loadTexture(assets[i].path, renderer, &gTextures);
        if (!tex) {
            printf("Failed to load asset: %s\n", assets[i].path);
            return 0;
        }
    }

    // Extra array and vector for the player assets
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

/**
* @brief free all the assets
* @param void
* @return void
*/
void freeAssets() {
    // Free all the textures
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

