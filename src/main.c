#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"
#include "user_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void draw_game(game_state* state) {
	BeginDrawing();

	ClearBackground(BLACK);
	draw_tilemap(*(state->world), state->worldOrigin, state->camera, state->tileSprites);
	draw_selected_tile(state);
	if(state->selectedTile.x >= 0 || state->selectedTile.y >= 0) {
		draw_game_UI(state);
	}

	EndDrawing();
}

int check_if_ui_closed() {
	vec2 mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	vec2 button;
	button.x = 9*WINDOW_WIDTH/10; 
	button.y = 9*WINDOW_HEIGHT/10;

	vec2 diff;
	diff.x = mouse.x - button.x;
	diff.y = mouse.y - button.y;

	double dist = (diff.x * diff.x) + (diff.y * diff.y);

	if(dist < (WINDOW_WIDTH/40 * WINDOW_WIDTH/40)) {
		return 1;
	}

	return 0;
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
		if(check_if_ui_closed()) {
			vec2 temp = {-1, -1};
			state->selectedTile = temp;
		}
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
		

		if(state.menuFlag == 1) {
			if(!draw_menu_screen(&state)) {
				printf("ERROR: failed to load tilemap.\n");
				return -1;
			}
		}

		else {

			//input stuff
			handle_input(&state);

			//actual draw
			draw_game(&state);
		}
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
