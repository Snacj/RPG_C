#include "gamepanel.h"
#include "assets.h"
#include "config.h"
#include "player.h"
#include "util.h"

#define FRAMERATE 60
#define FRAMEDELAY (1000 / FRAMERATE)

#define CEIL_DIV(a, b) (((a) + (b) - 1) / (b))

#define COLS CEIL_DIV(WINDOW_WIDTH, TILE_SIZE) 
#define ROWS CEIL_DIV(WINDOW_HEIGHT, TILE_SIZE)

Player player;

SDL_Rect stoneRect = { 10*TILE_SIZE, 10*TILE_SIZE, TILE_SIZE, TILE_SIZE };

static int update(void) {
    playerUpdate(&player);
    return 0;
}

static void draw(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_Texture* texture = *(SDL_Texture**)vector_get(&gTextures, 0);
    for(int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            SDL_Rect destRect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderCopy(renderer, texture, NULL, &destRect);
        }
    }
    texture = *(SDL_Texture**)vector_get(&gTextures, 2);
    SDL_RenderCopy(renderer, texture, NULL, &stoneRect);
    playerDraw(&player, renderer);
    SDL_RenderPresent(renderer);
}

void gamePanelLoop(SDL_Window* window, SDL_Renderer* renderer) {
    int quit = 0;
    SDL_Event e;
    playerInit(&player);

    while (!quit) {
        Uint32 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = 1;
            } 
        }
        update();
        draw(renderer);
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAMEDELAY) {
            SDL_Delay(FRAMEDELAY - frameTime);
        }
    }
}

