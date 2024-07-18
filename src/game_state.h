#pragma once

#include "../include/raylib.h"

#include "tilemap.h"

typedef struct game_state {

	//camera stuff
	//TODO: not sure if this should be a pointer instead?
	vec2 cameraPos;

	//art stuff
	Texture2D tileSprites[NUM_TILE_TYPES];

	//tilemap stuff
	//TODO: not sure if this should be a pointer or not
	tilemap* map;
	tile* selectedTile;
	//TODO: I think this will be useful to have but remove later if not.
	int selectedTileIndex;
} game_state;

int init_game_state(game_state* state); 

int move_camera(game_state* state, int key); 

int zoom_camera(game_state* state, int flag); 
