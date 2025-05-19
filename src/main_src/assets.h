#pragma once
#include <SDL2/SDL.h>
#include "../util/util.h"

extern Vector gTextures;
extern Vector gPlayerTextures;

typedef struct {
    const char* name;
    const char* path;
} TextureAsset;

int loadAssets(SDL_Renderer* renderer);
void freeAssets();
