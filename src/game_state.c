#include "game_state.h"
#include "tilemap.h"

#include <stdio.h>
#include <stdlib.h>

int load_art(game_state* state) {

	state->tileSprites[EMPTY] = LoadTexture("C:/polytopia_clone/sprites/tile cube.png");
	state->tileSprites[GRASS] = LoadTexture("C:/polytopia_clone/sprites/tile cube green.png");

	if(state->tileSprites !=0) {
		return 1;
	}

	return 0;
}

void init_mouse_info(game_state* state) {
	vec2 zeroVector = {0,0};
	state->mouseInfo.screenCell = zeroVector;
	state->mouseInfo.offset     = zeroVector;
	state->mouseInfo.worldCell  = zeroVector;
}

int init_game_state(game_state* state) {

	//TODO: origin should be calculated as center of screen in x axis?
	vec2 origin = {17, 1};

	state->worldOrigin = origin;
	state->world = 0;

	state->tileSprites = malloc(sizeof(Texture2D) * NUM_TILE_TYPES);

	if(!load_art(state)) {
		printf("ERROR: failed to load art.\n");
		return 0;
	}

	init_mouse_info(state);

	return 1;
}

void free_art(Texture2D* art) {
	free(art);
}

void update_mouse_info(mouse_info* info, double tileWidth, double tileHeight, vec2 origin) {
	vec2 mousePos;
	mousePos.x = GetMouseX();
	mousePos.y = GetMouseY();
	info->screenCell.x = ((int)mousePos.x)/((int)tileWidth);
	info->screenCell.y = ((int)mousePos.y)/((int)tileHeight);

	info->offset.x = ((int)mousePos.x)%((int)tileWidth);
	info->offset.y = ((int)mousePos.y)%((int)tileHeight);

	info->worldCell.x = (info->screenCell.y - origin.y) + (info->screenCell.x - origin.x);
	info->worldCell.y = (info->screenCell.y - origin.y) - (info->screenCell.x - origin.x);
}
