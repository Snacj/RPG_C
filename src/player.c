#include "player.h"
#include "config.h"

void playerInit(Player* player) {
    player->rect.x = 100;
    player->rect.y = 100;
    player->rect.w = TILE_SIZE;
    player->rect.h = TILE_SIZE;
    player->speed = 5;
}

void playerUpdate(Player* player) {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    float dx = 0;
    float dy = 0;

    if (keystates[SDL_SCANCODE_UP]) dy -= 1.0f;
    if (keystates[SDL_SCANCODE_DOWN]) dy += 1.0f;
    if (keystates[SDL_SCANCODE_LEFT]) dx -= 1.0f;
    if (keystates[SDL_SCANCODE_RIGHT]) dx += 1.0f;

    // Normalize manually for diagonal movement
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    player->rect.x += dx * player->speed;
    player->rect.y += dy * player->speed;

}

void playerDraw(Player* player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &player->rect);
}
