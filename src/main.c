#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"

#include <stdio.h>

int main() {


	//initialize raylib window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "polytopia clone");
	SetTargetFPS(144);

	//initialize tilemap
	//TODO: this should probably done in init_game_state
	tilemap map;
	vec2 size = {11, 11};
	create_tilemap(&map, size); 
	
	//initialize game state
	game_state state;

	if(!init_game_state(&state)) {
		printf("ERROR: failed to initialize game state.\n");
		return -1;
	}

	//set state's world to map
	state.world = &map;

	//draw loop
	while(!WindowShouldClose()) {

		//draw begins here
		BeginDrawing();

			ClearBackground(WHITE);

			draw_tilemap(*(state.world), state.worldOrigin, state.tileSprites);

		//draw ends here
		EndDrawing();
	}

	delete_tilemap(&map);
	free_art(state.tileSprites);

	return 0;
}
