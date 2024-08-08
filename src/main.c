#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void draw_game(game_state* state) {
	BeginDrawing();

	ClearBackground(BLACK);
	draw_tilemap(*(state->world), state->worldOrigin, state->camera, state->tileSprites);
	draw_selected_tile(state);
	EndDrawing();
}

void handle_input(game_state* state) {

	if(IsKeyDown(KEY_Q)) {
		zoom(state->world, 1, &(state->camera), state->worldOrigin);
	}
	if(IsKeyDown(KEY_E)) {
		zoom(state->world, 0, &(state->camera), state->worldOrigin);
	}

	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		select_tile(state);			
	}

	if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		move_camera(state);
	}
	else {
		state->mousePosPrev.x = GetMouseX();
		state->mousePosPrev.y = GetMouseY();
	}
}

int main() {

	srand(time(NULL));

	//initialize raylib window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "polytopia clone");
	SetTargetFPS(144);
	

	//initialize game state
	game_state state;

		//tilemap
		tilemap map;

	if(!init_game_state(&state, &map)) {
		printf("ERROR: failed to initialize game state.\n");
		return -1;
	}


	//draw loop
	while(!WindowShouldClose()) {
		
			//input stuff
			handle_input(&state);

			//actual draw
			draw_game(&state);
	}

	//save game before exit
	if(!save_tilemap_to_file(*(state.world), "tilemaps/tilemap.txt")) {
		printf("ERROR: failed to save game.\n");
		return -1;
	}

	//free all dynamically allocated memory
	destroy_game_state(&state);

	return 0;
}
