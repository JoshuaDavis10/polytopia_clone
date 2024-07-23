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

	//TODO: temporary. select_tile function will determine which tile is clicked so mouse info does not need to be a part of state. 
	//int selectedTileIndex;
	mouse_info mouseInfo;

	vec2 worldOrigin;
	//TODO: if tilemap is created in init_game_state, it shouldn't be a pointer right?
	//otherwise it would go out of scope? so like pass a pointer to state's tilemap into create_tilemap? idek
	tilemap* world;

	vec2 camera;
	
	Texture2D* tileSprites;

} game_state;

int init_game_state(game_state* state); 

void free_art(Texture2D* art);

void update_mouse_info(mouse_info* info, int tileWidth, int tileHeight, vec2 origin, vec2 camera);

void zoom(tilemap* map, int outFlag, vec2* camera, vec2 origin);

void move_camera(game_state* state, int direction); 
