#pragma once
#include <SDL2/SDL.h>
#include "util.h"

extern SDL_Texture* gTexture;
extern SDL_Texture* gPlainGrassTexture;
extern SDL_Texture* gPlayerTexture;
extern Vector gTextures;

typedef struct {
    const char* name;
    const char* path;
} TextureAsset;

int loadAssets(SDL_Renderer* renderer);
void freeAssets();
