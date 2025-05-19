#pragma once
#include <SDL2/SDL.h>

typedef struct {
    SDL_Texture *texture;
    SDL_Rect rect;
    int state;
} Button;

int button_is_hovered(SDL_Rect button, int x, int y);
Button create_button(Button *button, SDL_Renderer *renderer, int x, int y, int w, int h, int iTexture);
void init_main_menu(SDL_Renderer *renderer);
void mainMenuDraw(SDL_Renderer *renderer);
void handle_main_menu_events(SDL_Event *event);
