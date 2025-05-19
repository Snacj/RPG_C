/*
 * player.c
 *
 * This file handles the player
 *
 */
#include "player.h"
#include "../config.h"
#include "../main_src/assets.h"
#include "../main_src/collisionchecker.h"

SDL_Rect stoneRect1 = { 10*TILE_SIZE, 10*TILE_SIZE, TILE_SIZE, TILE_SIZE };

enum playerDirection {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

/**
* @brief initialize the player
* @param player the player to initialize
* @return void
*/
void playerInit(Player* player) {
    player->rect.x = 100;
    player->rect.y = 100;
    player->rect.w = TILE_SIZE;
    player->rect.h = TILE_SIZE;

    player->solidArea.w = TILE_SIZE / 2;
    player->solidArea.h = TILE_SIZE / 2;

    player->solidArea.x = player->rect.x + (player->rect.w - player->solidArea.w) / 2;
    player->solidArea.y = player->rect.y + player->rect.h - player->solidArea.h;

    player->speed = PLAYER_SPEED;
    player->direction = DOWN;
    player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 0);

    player->animationTimer = 0;
    player->currentAnimationFrame = 0;
    player->idle = 1;

    // DEBUG default false
    player->debug = 0;
}

/**
* @brief update the player
* @param player the player to update
* @return void
*/
void playerUpdate(Player* player) {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    // Handles animation
    player->animationTimer++;
    if (player->animationTimer >= 15) {
        player->animationTimer = 0;
        player->currentAnimationFrame = (player->currentAnimationFrame + 1) % 2;
    }


    float dx = 0;
    float dy = 0;

    // Handle Keyboard input
    if (keystates[SDL_SCANCODE_W]) {
        player->direction = UP;
        dy = -1.0f;
        if (player->currentAnimationFrame == 0) {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 6);
        } else {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 7);
        }
    }
    if (keystates[SDL_SCANCODE_S]) {
        player->direction = DOWN;
        dy = 1.0f;
        if (player->currentAnimationFrame == 0) {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 2);
        } else {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 3);
        }
    }
    if (keystates[SDL_SCANCODE_A]) {
        player->direction = LEFT;
        dx = -1.0f;
        if (player->currentAnimationFrame == 0) {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 14);
        } else {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 15);
        }
    }
    if (keystates[SDL_SCANCODE_D]) {
        player->direction = RIGHT;
        dx = 1.0f;
        if (player->currentAnimationFrame == 0) {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 10);
        } else {
            player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 11);
        }
    }
    if (!keystates[SDL_SCANCODE_W] && !keystates[SDL_SCANCODE_S] &&
        !keystates[SDL_SCANCODE_A] && !keystates[SDL_SCANCODE_D]) {
        player->idle = 1;
        if (player->direction == UP) {
            if (player->currentAnimationFrame == 0) {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 4);
            } else {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 5);
            }
        } else if (player->direction == DOWN) {
            if (player->currentAnimationFrame == 0) {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 0);
            } else {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 1);
            }
        } else if (player->direction == LEFT) {
            if (player->currentAnimationFrame == 0) {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 12);
            } else {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 13);
            }
        } else if (player->direction == RIGHT) {
            if (player->currentAnimationFrame == 0) {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 8);
            } else {
                player->texture = *(SDL_Texture**)vector_get(&gPlayerTextures, 9);
            }
        }
    } else {
        player->idle = 0;
    }
    if (keystates[SDL_SCANCODE_O]) {
        player->debug = !player->debug;
    }

    // Normalize diagonal movement
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    // Check for collisions with the stone
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


/**
* @brief draw the player
* @param player the player to draw, SDL_Renderer*
* @return void
*/
void playerDraw(Player* player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    // DEBUG
    if (player->debug) {
        SDL_RenderDrawRect(renderer, &player->solidArea);
    }
}
