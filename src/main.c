#include "../include/raylib.h"

#include "tilemap.h"
#include "files.h"
#include "defines.h"
#include "game_state.h"
#include "input.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {
	srand(time(NULL));

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "polytopia clone");
	SetTargetFPS(144);

	tilemap map;
	if(!(load_tilemap_random(&map, 11, 11))) {
		printf("Error. Failed to load tilemap from file.\n");
		return -1;
	}

	game_state state;
	if(!(init_game_state(&state))) {
		printf("Error. Failed to initialize game state.\n");
		return -1;
	}

	state.map = &map;

	while(!WindowShouldClose()) {
		process_input(&state);

		BeginDrawing();

		ClearBackground(BLACK);
		draw_tilemap(*(state.map), state.cameraPos, state.tileSprites);

		EndDrawing();
	}
	
	destroy_tilemap(&map);

	return 0;
}
