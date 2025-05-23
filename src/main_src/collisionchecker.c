/*
* collisionchecker.c
*
* This file is checking for collisions
*
*/
#include "collisionchecker.h"
#include "../entity/player.h"

#include <SDL2/SDL.h>

extern Player player;

enum {
  COLLISION_NONE = 0,
  COLLISION_TOP = 1,
  COLLISION_BOTTOM = 2,
  COLLISION_LEFT = 3,
  COLLISION_RIGHT = 4
};

/**
* @brief check for collision between two rectangles
* @param a the first rectangle, b the second rectangle
* @return int
*/
int checkCollision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w <= b.x || a.x >= b.x + b.w || a.y + a.h <= b.y ||
        a.y >= b.y + b.h) {
    // printf("No collision\n");
    return COLLISION_NONE;
    }

    int dxLeft = abs((a.x + a.w) - b.x);
    int dxRight = abs(a.x - (b.x + b.w));
    int dyTop = abs((a.y + a.h) - b.y);
    int dyBottom = abs(a.y - (b.y + b.h));

    int minX = dxLeft < dxRight ? dxLeft : dxRight;
    int minY = dyTop < dyBottom ? dyTop : dyBottom;

    if (minX < minY) {
        if (dxLeft < dxRight) {
            // printf("Collision on RIGHT\n");
            return COLLISION_RIGHT;
        } else {
            // printf("Collision on LEFT\n");
            return COLLISION_LEFT;
        }
        } else {
        if (dyTop < dyBottom) {
            // printf("Collision on BOTTOM\n");
            return COLLISION_BOTTOM;
        } else {
            // printf("Collision on TOP\n");
            return COLLISION_TOP;
        }
    }
    return COLLISION_NONE;
}
