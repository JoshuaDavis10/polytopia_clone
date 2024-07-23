#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"

#include <stdio.h>

//TODO: delete this later. used for testing
void display_mouse_info(mouse_info* info) {
	char buf[100];
	snprintf(buf, 100, "Mouse Position:    (%d, %d)", GetMouseX(), GetMouseY());
	DrawText(buf, 50, 50, 10, BLACK);
	snprintf(buf, 100, "Mouse Screen Cell: (%d, %d)", info->screenCell.x, info->screenCell.y);
	DrawText(buf, 50, 75, 10, BLACK);
	snprintf(buf, 100, "Mouse World Cell:  (%d, %d)", info->worldCell.x, info->worldCell.y);
	DrawText(buf, 50, 100, 10, BLACK);
	snprintf(buf, 100, "Mouse Offset    :  (%d, %d)", info->offset.x, info->offset.y);
	DrawText(buf, 50, 125, 10, BLACK);
}

//TODO: delete this later. or move to game_state. could have like a draw_game function that draws selected tile, units
//tilemap, etc...
void draw_selected(game_state* state) {

	Vector2 screenCoords;
	screenCoords.x = state->worldOrigin.x * state->world->tile_width  + (state->mouseInfo.worldCell.x - state->mouseInfo.worldCell.y) *  (state->world->tile_width/2) - state->camera.x;
	screenCoords.y = state->worldOrigin.y * state->world->tile_height + (state->mouseInfo.worldCell.x + state->mouseInfo.worldCell.y) * (state->world->tile_height/2) - state->camera.y;
	DrawTextureEx(state->tileSprites[SELECTED], screenCoords, 0.0f, ((double)state->world->tile_width)/TILE_SPRITE_WIDTH, WHITE);

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
	//TODO: should also be done in init_game_state
	state.world = &map;

	//draw loop
	while(!WindowShouldClose()) {

		//draw begins here
		BeginDrawing();

			ClearBackground(WHITE);

			draw_tilemap(*(state.world), state.worldOrigin, state.camera, state.tileSprites);
			update_mouse_info(&(state.mouseInfo), state.world->tile_width, state.world->tile_height, state.worldOrigin, state.camera);
			display_mouse_info(&(state.mouseInfo));
			draw_selected(&state);

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

		//draw ends here
		EndDrawing();
	}

	delete_tilemap(&map);
	free_art(state.tileSprites);

	return 0;
}
