#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>

extern SDL_Texture* gTexture;
extern SDL_Texture* gPlainGrassTexture;
extern SDL_Texture* gPlayerTexture;

int loadAssets(SDL_Renderer* renderer);
void freeAssets();

#endif // ASSETS_H

