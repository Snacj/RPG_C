#include "player.h"
#include "config.h"
#include "assets.h"
#include "collisionchecker.h"

SDL_Rect stoneRect1 = { 10*TILE_SIZE, 10*TILE_SIZE, TILE_SIZE, TILE_SIZE };

enum playerDirection {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

void playerInit(Player* player) {
    player->rect.x = 100;
    player->rect.y = 100;
    player->rect.w = TILE_SIZE;
    player->rect.h = TILE_SIZE;

    player->solidArea.w = 32;
    player->solidArea.h = 32;

    player->solidArea.x = player->rect.x + (player->rect.w - player->solidArea.w) / 2;
    player->solidArea.y = player->rect.y + player->rect.h - player->solidArea.h;

    player->speed = 5;
    player->direction = DOWN;
    player->texture = *(SDL_Texture**)vector_get(&gTextures, 3);
}

void playerUpdate(Player* player) {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    float dx = 0;
    float dy = 0;

    if (keystates[SDL_SCANCODE_W]) {
        player->direction = UP;
        dy -= 1.0f;
    }
    if (keystates[SDL_SCANCODE_S]) {
        player->direction = DOWN;
        dy += 1.0f;
    }
    if (keystates[SDL_SCANCODE_A]) {
        player->direction = LEFT;
        dx -= 1.0f;
    }
    if (keystates[SDL_SCANCODE_D]) {
        player->direction = RIGHT;
        dx += 1.0f;
    }

    // Normalize diagonal movement
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    SDL_Rect futureRect = player->rect;
    futureRect.x += dx * player->speed;
    SDL_Rect futureSolid = {
        futureRect.x + (player->rect.w - player->solidArea.w) / 2,
        futureRect.y + (player->rect.h - player->solidArea.h),
        player->solidArea.w,
        player->solidArea.h
    };

    if (checkCollision(futureSolid, stoneRect1) == 0) {
        player->rect.x = futureRect.x;
    }

    futureRect = player->rect;
    futureRect.y += dy * player->speed;
    futureSolid.x = futureRect.x + (player->rect.w - player->solidArea.w) / 2;
    futureSolid.y = futureRect.y + (player->rect.h - player->solidArea.h);

    if (checkCollision(futureSolid, stoneRect1) == 0) {
        player->rect.y = futureRect.y;
    }

    player->solidArea.x = player->rect.x + (player->rect.w - player->solidArea.w) / 2;
    player->solidArea.y = player->rect.y + (player->rect.h - player->solidArea.h);


}


void playerDraw(Player* player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &player->solidArea);
    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
}
