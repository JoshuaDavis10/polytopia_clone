#pragma once

#include "math.h"

typedef struct game_state {
	vec2 mousePos;
	vec2 mouseScreenCell;
	vec2 mouseOffset;
	vec2 mouseWorldCell;
} game_state;

int init_game_state(game_state* state); 
