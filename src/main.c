#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"

#include <stdio.h>

int main() {

	//initialize tilemap
	tilemap map;
	vec2 size = {11, 11};
	create_tilemap(&map, size); 
	
	//initialize game state
	game_state state;

	if(!init_game_state(&state)) {
		printf("ERROR: failed to initialize game state.\n");
	}

	//set state's world to map
	state->world = &map;

	return 0;
}
