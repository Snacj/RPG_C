#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#define MAP_ROWS 100
#define MAP_COLS 100
#define LINE_LENGTH 256

typedef struct {
    int worldX;
    int worldY;
    SDL_Rect solidArea;
    SDL_Texture* texture;
} Tile;

extern int MAP[MAP_ROWS][MAP_COLS];

int readMap(const char* path);
