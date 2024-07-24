#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"

#include <stdio.h>


int main() {

	//initialize raylib window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "polytopia clone");
	SetTargetFPS(144);
	

	//initialize game state
	game_state state;

		//tilemap
		tilemap map;
		vec2 size = {3, 3};

	if(!init_game_state(&state, &map, size)) {
		printf("ERROR: failed to initialize game state.\n");
		return -1;
	}


	//draw loop
	while(!WindowShouldClose()) {

		//input handling

			if(IsKeyDown(KEY_Q)) {
				zoom(state.world, 1, &(state.camera), state.worldOrigin);
			}
			if(IsKeyDown(KEY_E)) {
				zoom(state.world, 0, &(state.camera), state.worldOrigin);
			}

			if(IsKeyDown(KEY_W)) {
				move_camera(&state, UP);
			}
			if(IsKeyDown(KEY_S)) {
				move_camera(&state, DOWN);
			}
			if(IsKeyDown(KEY_D)) {
				move_camera(&state, RIGHT);
			}
			if(IsKeyDown(KEY_A)) {
				move_camera(&state, LEFT);
			}
			if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				select_tile(&state);			
			}

		//draw begins here
		BeginDrawing();

			ClearBackground(BLACK);
			draw_tilemap(*(state.world), state.worldOrigin, state.camera, state.tileSprites);
			draw_selected_tile(&state);

		//draw ends here
		EndDrawing();
	}

	//free all dynamically allocated memory
	destroy_game_state(&state);

	return 0;
}
