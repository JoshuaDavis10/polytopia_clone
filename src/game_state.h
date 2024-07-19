#pragma once

#include "math.h"
#include "tilemap.h"

typedef struct mouse_info {

	//TODO: screencell and offset can be temporary for printing to screen for testing
	vec2 screenCell;
	vec2 offset;
	vec2 worldCell;

} mouse_info;

typedef struct game_state {

	mouse_info mouseInfo;

	vec2 worldOrigin;
	tilemap* world;
	
	Texture2D* tileSprites;

} game_state;

int init_game_state(game_state* state); 

void free_art(Texture2D* art);

void update_mouse_info(mouse_info* info, double tileWidth, double tileHeight, vec2 origin);
