#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    SDL_Rect solidArea;
    SDL_Texture* texture;
    int speed;
    int direction;

} Player;

void playerInit(Player* player);

void playerUpdate(Player* player);

void playerDraw(Player* player, SDL_Renderer* renderer);

#endif // PLAYER_H
