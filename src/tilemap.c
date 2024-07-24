#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "files.h"

#include <stdlib.h>
#include <stdio.h>

//TODO: this function can be expanded into the random generation and loading tilemap from files functions whenever you re-integrate the file stuff
//TODO: delete this it is useless pretty much lol
/*
void create_tilemap(tilemap* map, vec2 mapsize) {
	map->mapsize = mapsize;
	map->tile_width  = TILE_SPRITE_WIDTH;
	map->tile_height = TILE_SPRITE_HEIGHT;
	map->tiles = malloc(sizeof(int) * (mapsize.x * mapsize.y));
	for(int i = 0; i < (mapsize.x * mapsize.y); i++) {
		map->tiles[i] = 0;
	}
		map->tiles[0] = 2;
		map->tiles[1] = 0;
		map->tiles[2] = 1;
		map->tiles[3] = 3;
		map->tiles[4] = 1;
		map->tiles[5] = 2;
		map->tiles[6] = 5;
		map->tiles[7] = 3;
		map->tiles[8] = 4;
}
*/

int load_tilemap_from_file(tilemap* map, const char* path) {

	//open file
	file mapfile;

	//error checking for file open
	if(!open_file(path, &mapfile, "r")) {
		printf("Failed to open file: %s.\n", path);
		return 0;
	}
	
	//dynamically allocate memory for tiles
	map->tile_width  = TILE_SPRITE_WIDTH * 4;
	map->tile_height = TILE_SPRITE_HEIGHT * 4;
	map->mapsize.x = atoi(read_line(mapfile));
	map->mapsize.y = atoi(read_line(mapfile));
	
	map->tiles = malloc(sizeof(int) * (map->mapsize.x * map->mapsize.y));

	//read lines from file
	//and load data into tilemap
	for(int i = 0 ; i < (map->mapsize.x * map->mapsize.y); i++) {
		map->tiles[i] = atoi(read_line(mapfile));
	}

	//close file
	if(!close_file(&mapfile)) {
		printf("Failed to close file: %s.\n", path);
		return 0;
	}

	//success
	return 1;
}

int save_tilemap_to_file(tilemap map, const char* path) {

	//open file
	file mapfile;

	//error checking for file open
	if(!open_file(path, &mapfile, "w")) {
		printf("Failed to open file: %s.\n", path);
		return 0;
	}

	//save mapsize to file
	char buffer[100];
	snprintf(buffer, 100, "%d", map.mapsize.x);
	write_line(mapfile, buffer);
	snprintf(buffer, 100, "%d", map.mapsize.y);
	write_line(mapfile, buffer);

	//iterate through tiles and write each tile's type as a line in the file
	for(int i = 0; i < (map.mapsize.x * map.mapsize.y); i++) {
		snprintf(buffer, 100, "%d", map.tiles[i]);
		write_line(mapfile, buffer);
	}

	//close file
	if(!close_file(&mapfile)) {
		printf("Failed to close file: %s.\n", path);
		return 0;
	}

	//success
	return 1;
}

void load_tilemap_random(tilemap* map, vec2 mapsize) {

	//dynamically allocate memory for tiles
	map->tiles = malloc(sizeof(int) * (mapsize.x * mapsize.y));
	map->mapsize = mapsize;
	map->tile_width  = TILE_SPRITE_WIDTH  * 4;
	map->tile_height = TILE_SPRITE_HEIGHT * 4;

	//iterate through all tiles and randomly select a tiletype
	int r;

	for(int i = 0; i < (mapsize.x * mapsize.y); i++) { 
		r = rand() % (NUM_TILE_TYPES - 1);
		map->tiles[i] = r;
	}

	//TODO: the random map generation will obviously change a lot but for now make it literally completely random

}

void draw_tilemap(tilemap map, vec2 origin, vec2 camera, Texture2D* sprites) {
	
	Vector2 screenCoords;
	
	int heightOffset;

	for(int y = 0; y < map.mapsize.y; y++) {
		for(int x = 0; x < map.mapsize.x; x++) {

			//TODO: future sprites will need height offsets
			heightOffset = 0;
			if(map.tiles[y*(map.mapsize.y) + x] == MOUNTAIN) {
				heightOffset = 4 * map.tile_height/TILE_SPRITE_HEIGHT;
			}

			screenCoords.x = (origin.x * map.tile_width)  + ((x-y) * (map.tile_width/2)) - camera.x;
			screenCoords.y = (origin.y * map.tile_height) + ((x+y) * (map.tile_height/2)) - camera.y - heightOffset;
			DrawTextureEx(sprites[map.tiles[y*(map.mapsize.y) + x]], screenCoords, 0.0f, ((double)map.tile_width)/TILE_SPRITE_WIDTH, WHITE);
		}
	}
}

void destroy_tilemap(tilemap* map) {
	free(map->tiles);
}
