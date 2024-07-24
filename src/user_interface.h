#pragma once

#include "../include/raylib.h"

#include "defines.h"
#include "game_state.h"

#define BUTTON_WIDTH WINDOW_WIDTH/10
#define BUTTON_HEIGHT WINDOW_HEIGHT/20

int draw_menu_screen(game_state* state); 

void draw_game_UI(game_state* state); 
