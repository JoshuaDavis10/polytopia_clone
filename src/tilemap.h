#pragma once

#include "../include/raylib.h"

#include "math.h"

#define FRUIT_CHANCE 18
#define CROP_CHANCE 18
#define FIELD_CHANCE 12
#define ANIMAL_CHANCE 19
#define FOREST_CHANCE 19
#define MOUNTAIN_CHANCE 3
#define METAL_CHANCE 11

#define FRUIT_THRESHOLD FRUIT_CHANCE
#define CROP_THRESHOLD (FRUIT_THRESHOLD + CROP_CHANCE)
#define FIELD_THRESHOLD (CROP_THRESHOLD + FIELD_CHANCE)
#define ANIMAL_THRESHOLD (FIELD_THRESHOLD + ANIMAL_CHANCE)
#define FOREST_THRESHOLD (ANIMAL_THRESHOLD + FOREST_CHANCE)
#define MOUNTAIN_THRESHOLD (FOREST_THRESHOLD + MOUNTAIN_CHANCE)
#define METAL_THRESHOLD (MOUNTAIN_THRESHOLD + METAL_CHANCE)

//enumeration for tile type
typedef enum tile_type {
	FIELD,
	FOREST,
	MOUNTAIN,
	WATER,
	OCEAN,  
	VILLAGE,
	SELECTED,
	/*
	FRUIT,
	CROP,
	FIELD,
	ANIMAL,
	FOREST,
	MOUNTAIN,
	METAL,
	*/
	NUM_TILE_TYPES
	
} tile_type;

typedef struct tilemap {

	//dimensions
	vec2 mapsize;

	//array of all tiles in the tilemap (array size is width*height)
	int* tiles;

	//tile dimensions
	//TODO: change this to a vec2
	int tile_width;
	int tile_height;

} tilemap;

void create_tilemap(tilemap* map, vec2 mapsize);

int load_tilemap_from_file(tilemap* map, const char* path); 

void load_tilemap_random(tilemap* map, vec2 mapsize); 

int save_tilemap_to_file(tilemap map, const char* path);

void draw_tilemap(tilemap map, vec2 origin, vec2 camera, Texture2D* sprites);

void destroy_tilemap(tilemap* map);
