#pragma once

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
	FRUIT,
	CROP,
	FIELD,
	ANIMAL,
	FOREST,
	MOUNTAIN,
	METAL,
	NUM_TILE_TYPES
} tile_type;

typedef struct tile {
	vec2 position;
	tile_type type;
} tile;

typedef struct tilemap {

	//dimensions
	int width;
	int height;

	//array of all tiles in the tilemap (array size is width*height)
	tile* tiles;

	//tile dimensions
	double tile_width;
	double tile_height;
} tilemap;

int load_tilemap_from_file(tilemap* tilemap, const char* path);

int load_tilemap_random(tilemap* tilemap, int width, int height);

int write_tilemap_to_file(tilemap* tilemap, const char* path); 

int destroy_tilemap(tilemap* tilemap);

void draw_tilemap(tilemap tilemap, vec2 center, Texture2D* sprites);

void draw_tile(tile tile, int tile_width, int tile_height, vec2 center, Texture2D* sprites);

