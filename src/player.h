#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    int speed;

} Player;

void playerInit(Player* player);

void playerUpdate(Player* player);

void playerDraw(Player* player, SDL_Renderer* renderer);

#endif // PLAYER_H
