#include "main_menu.h"
#include "../main_src/assets.h"
#include "../config.h"
#include "../main_src//gamepanel.h"
#include <SDL2/SDL.h>

Button start_game_button;
Button exit_game_button;
GamePanel gamePanel;

Button create_button(Button *button, SDL_Renderer *renderer, int x, int y, int w, int h, int iTexture) {
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;

    // Load the texture
    button->texture = *(SDL_Texture**)vector_get(&gTextures, iTexture); 
    if (!button->texture) {
        printf("Failed to create texture! SDL Error: %s\n", SDL_GetError());

    }
    button->state = 0;
    return *button;
}


int button_is_hovered(SDL_Rect button, int x, int y) {

    if (x >= button.x && x <= button.x + button.w &&
        y >= button.y && y <= button.y + button.h) {
        return 1;
    }
    return 0;

}

void init_main_menu(SDL_Renderer *renderer) {
    // Initialize the button
    int button_scale = 4;
    create_button(
        &start_game_button,
        renderer,
        WINDOW_WIDTH  / 2 - (32 * button_scale) / 2,
        WINDOW_HEIGHT / 2 - (16 * button_scale) / 2,
        32 * button_scale,
        16 * button_scale,
        4
    );
    create_button(
        &exit_game_button,
        renderer,
        WINDOW_WIDTH  / 2 - (32 * button_scale) / 2,
        WINDOW_HEIGHT / 2 - (16 * button_scale) / 2 + 75,
        32 * button_scale,
        16 * button_scale,
        5
    );
}

void mainMenuDraw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, *(SDL_Texture**)vector_get(&gTextures, 3), NULL, &destRect);
    SDL_RenderCopy(renderer, start_game_button.texture, NULL, &start_game_button.rect);
    SDL_RenderCopy(renderer, exit_game_button.texture, NULL, &exit_game_button.rect);
}

static void button_click(Button *button) {
        button->state = 1;
        button->rect.x += 5;
        button->rect.y += 5;
        button->rect.w -= 10;
        button->rect.h -= 10;
}

static void button_release(Button *button) {
        button->state = 0;
        button->rect.x -= 5;
        button->rect.y -= 5;
        button->rect.w += 10;
        button->rect.h += 10;
}

void handle_main_menu_events(SDL_Event *event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (button_is_hovered(start_game_button.rect, x, y)) {
            button_click(&start_game_button);
        }
        if (button_is_hovered(exit_game_button.rect, x, y)) {
            button_click(&exit_game_button);
        }

    } else if (event->type == SDL_MOUSEBUTTONUP) {
        if (start_game_button.state == 1) {
            if (button_is_hovered(start_game_button.rect, x, y)) {
                button_release(&start_game_button);
                gamePanel.gameState = GAME;
            } else {
                button_release(&start_game_button);
            }
        }

        if (exit_game_button.state == 1) {
            if (button_is_hovered(exit_game_button.rect, x, y)) {
                button_release(&exit_game_button);
                gamePanel.running = 0;
            } else {
                button_release(&exit_game_button);
            }
        }
    }
}


