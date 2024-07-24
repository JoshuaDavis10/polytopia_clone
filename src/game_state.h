#pragma once

#include "math.h"
#include "tilemap.h"

typedef struct game_state {

	//flag for in game or in menu
	int menuFlag;

	//tilemap stuff
	vec2 worldOrigin;
	tilemap* world;
	vec2 selectedTile;

	//camera
	vec2 camera;
	vec2 mousePosPrev;
	
	//art
	Texture2D* tileSprites;

} game_state;

int init_game_state(game_state* state, tilemap* world); 

void destroy_game_state(game_state* state); 

void select_tile(game_state* state);

void draw_selected_tile(game_state* state);

void zoom(tilemap* map, int outFlag, vec2* camera, vec2 origin);

void move_camera(game_state* state); 
