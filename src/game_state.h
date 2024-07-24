#pragma once

#include "math.h"
#include "tilemap.h"

typedef enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
} direction;

typedef struct mouse_info {

	//TODO: screencell and offset can be temporary for printing to screen for testing
	vec2 screenCell;
	vec2 offset;

	//this can be used to calculate index of tile selected
	vec2 worldCell;

} mouse_info;

typedef struct game_state {

	//tilemap stuff
	vec2 worldOrigin;
	tilemap* world;
	vec2 selectedTile;

	//camera
	vec2 camera;
	
	//art
	Texture2D* tileSprites;

} game_state;

int init_game_state(game_state* state, tilemap* world, vec2 worldSize); 

void destroy_game_state(game_state* state); 

void select_tile(game_state* state);

void draw_selected_tile(game_state* state);

void zoom(tilemap* map, int outFlag, vec2* camera, vec2 origin);

void move_camera(game_state* state, int direction); 
