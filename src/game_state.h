#pragma once

#include "math.h"
#include "tilemap.h"

typedef struct game_state {
	vec2 worldOrigin;
	tilemap* world;
	Texture2D* tileSprites;
} game_state;

int init_game_state(game_state* state); 

void free_art(Texture2D* art);
