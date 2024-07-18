#include "game_state.h"
#include "tilemap.h"

#include <stdio.h>
#include <stdlib.h>

int load_art(game_state* state) {
	state->tileSprites[0] = LoadTexture("C:/polytopia_clone/sprites/tile 40x40.png");
	if(state->tileSprites !=0) {
		return 1;
	}
	return 0;
}

int init_game_state(game_state* state) {
	vec2 origin = {10, 2};
	state->worldOrigin = origin;
	state->world = 0;
	state->tileSprites = malloc(sizeof(Texture2D) * NUM_TILE_TYPES);
	if(!load_art(state)) {
		printf("ERROR: failed to load art.\n");
		return 0;
	}
	return 1;
}

void free_art(Texture2D* art) {
	free(art);
}
