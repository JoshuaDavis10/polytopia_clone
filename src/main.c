#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"

#include <stdio.h>

void display_mouse_info(mouse_info* info) {
	char buf[100];
	snprintf(buf, 100, "Mouse Position:    (%d, %d)", (int)GetMouseX(), (int)GetMouseY());
	DrawText(buf, 50, 50, 10, BLACK);
	snprintf(buf, 100, "Mouse Screen Cell: (%d, %d)", (int)info->screenCell.x, (int)info->screenCell.y);
	DrawText(buf, 50, 75, 10, BLACK);
	snprintf(buf, 100, "Mouse World Cell:  (%d, %d)", (int)info->worldCell.x, (int)info->worldCell.y);
	DrawText(buf, 50, 100, 10, BLACK);
}

void draw_selected(game_state* state) {

	DrawRectangle(state->mouseInfo.screenCell.x * state->world->tile_width, state->mouseInfo.screenCell.y * state->world->tile_height, state->world->tile_width, state->world->tile_height, BLUE);

	//screenCoords.x = origin.x * map.tile_width  + (x-y) * (map.tile_width/2);
	//screenCoords.y = origin.y * map.tile_height + (x+y) * (map.tile_height/2);
	
}

int main() {


	//initialize raylib window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "polytopia clone");
	SetTargetFPS(144);

	//initialize tilemap
	//TODO: this should probably done in init_game_state
	tilemap map;
	vec2 size = {30, 30};
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
			update_mouse_info(&(state.mouseInfo), state.world->tile_width, state.world->tile_height, state.worldOrigin);
			display_mouse_info(&(state.mouseInfo));
			draw_selected(&state);

		//draw ends here
		EndDrawing();
	}

	delete_tilemap(&map);
	free_art(state.tileSprites);

	return 0;
}
