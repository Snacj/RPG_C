#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <SDL2/SDL.h>

typedef enum {
    MAIN_MENU,
    GAME,
} GameState;

typedef struct {
    GameState gameState;
    int running;
} GamePanel;

extern GamePanel gamePanel;

void gamePanelLoop(SDL_Window* window, SDL_Renderer* renderer);

#endif // GAMEPANEL_H

