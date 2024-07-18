#include "game_state.h"

#include "tilemap.h"
#include "defines.h"

#include <stdio.h>

#define CAMERA_MOVE_SPEED 0.02f
#define CAMERA_ZOOM_SPEED 0.01f

#define WINDOW_CENTER_Y WINDOW_HEIGHT/2
#define WINDOW_CENTER_X WINDOW_WIDTH/2

#define MIN_ZOOM 100.0f
#define MAX_ZOOM 400.0f

int init_game_state(game_state* state) {
	vec2 camera = {(double)WINDOW_WIDTH/2, (double)WINDOW_HEIGHT/2};
	state->cameraPos = camera;

	//TODO: draw custom tiles for each tile type and load them here
	state->tileSprites[FRUIT] = LoadTexture("sprites/tile2.png");
	state->tileSprites[CROP] = LoadTexture("sprites/tile2.png");
	state->tileSprites[FIELD] = LoadTexture("sprites/tile2.png");
	state->tileSprites[ANIMAL] = LoadTexture("sprites/tile2.png");
	state->tileSprites[FOREST] = LoadTexture("sprites/tile2.png");
	state->tileSprites[MOUNTAIN] = LoadTexture("sprites/tile2.png");
	state->tileSprites[METAL] = LoadTexture("sprites/tile2.png");

	//initialize map and selected tile to 0 (a map will be loaded once the player has created a new game or selected a saved game)
	state->map = 0;
	state->selectedTile = 0;

	//TODO: return 0 if fail to initialize. can't really fail now,
	//but later this function will be much more complicated.
	return 1;
}

int move_camera(game_state* state, int key) {
	//TODO: check for like an out of bounds. i.e. camera shouldn't move past a certain point in all directions
	switch(key) {
		case KEY_A:
			state->cameraPos.x+=CAMERA_MOVE_SPEED*state->map->tile_width;
			break;
		case KEY_W:
			state->cameraPos.y+=CAMERA_MOVE_SPEED*state->map->tile_width;
			break;
		case KEY_D:
			state->cameraPos.x-=CAMERA_MOVE_SPEED*state->map->tile_width;
			break;
		case KEY_S:
			state->cameraPos.y-=CAMERA_MOVE_SPEED*state->map->tile_width;
			break;
		default:
			printf("ERROR: key other than 'w, a, s, or d' was passed into move_camera function.\n");
			return 0;
	}

	return 1;
}

//TODO: there's a lot of hardcoded numbers in this function... kinda awkward
int zoom_camera(game_state* state, int flag) {
	int distX = state->cameraPos.x - WINDOW_CENTER_X;
	int distY = state->cameraPos.y - WINDOW_CENTER_Y;
	if(flag) {
		if(state->map->tile_width < MIN_ZOOM) {
			return 1;
		}
		state->map->tile_width-=CAMERA_ZOOM_SPEED*state->map->tile_width;
		state->map->tile_height-=CAMERA_ZOOM_SPEED*state->map->tile_height;
		state->cameraPos.x-=distX/100.0f;
		state->cameraPos.y-=distY/100.0f;
		return 1;
	}
	else {
		if(state->map->tile_width > MAX_ZOOM) {
			return 1;
		}
		state->map->tile_width+=CAMERA_ZOOM_SPEED*state->map->tile_width;
		state->map->tile_height+=CAMERA_ZOOM_SPEED*state->map->tile_height;
		state->cameraPos.x+=distX/100.0f;
		state->cameraPos.y+=distY/100.0f;
		return 1;
	}
}
