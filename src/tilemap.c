#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"

#include <stdlib.h>
#include <stdio.h>

void create_tilemap(tilemap* map, vec2 mapsize) {
	map->mapsize = mapsize;
	map->tile_width  = TILE_SPRITE_WIDTH;
	map->tile_height = TILE_SPRITE_HEIGHT;
	map->tiles = malloc(sizeof(int) * (mapsize.x * mapsize.y));
	for(int i = 0; i < (mapsize.x * mapsize.y); i++) {
		map->tiles[i] = 0;
	}
}

void draw_tilemap(tilemap map, vec2 origin, Texture2D* sprites) {
	
	vec2 screenCoords;
	
	for(int y = 0; y < map.mapsize.y; y++) {
		for(int x = 0; x < map.mapsize.x; x++) {
			screenCoords.x = (origin.x * map.tile_width)  + ((x-y) * (map.tile_width/2));
			screenCoords.y = (origin.y * map.tile_height) + ((x+y) * (map.tile_height/2));
			DrawTexture(sprites[map.tiles[y*((int)map.mapsize.y) + x]], screenCoords.x, screenCoords.y, WHITE);
		}
	}
}

void delete_tilemap(tilemap* map) {
	free(map->tiles);
}
