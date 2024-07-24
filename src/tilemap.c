#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"

#include <stdlib.h>
#include <stdio.h>

//TODO: this function can be expanded into the random generation and loading tilemap from files functions whenever you re-integrate the file stuff
void create_tilemap(tilemap* map, vec2 mapsize) {
	map->mapsize = mapsize;
	map->tile_width  = TILE_SPRITE_WIDTH;
	map->tile_height = TILE_SPRITE_HEIGHT;
	map->tiles = malloc(sizeof(int) * (mapsize.x * mapsize.y));
	for(int i = 0; i < (mapsize.x * mapsize.y); i++) {
		map->tiles[i] = 0;
	}
}

void draw_tilemap(tilemap map, vec2 origin, vec2 camera, Texture2D* sprites) {
	
	Vector2 screenCoords;
	
	//TODO: adjust y coordinate of tile depending on tile type (basically, some will be taller. like mountains for example)

	for(int y = 0; y < map.mapsize.y; y++) {
		for(int x = 0; x < map.mapsize.x; x++) {
			screenCoords.x = (origin.x * map.tile_width)  + ((x-y) * (map.tile_width/2)) - camera.x;
			screenCoords.y = (origin.y * map.tile_height) + ((x+y) * (map.tile_height/2)) - camera.y;
			DrawTextureEx(sprites[map.tiles[y*(map.mapsize.y) + x]], screenCoords, 0.0f, ((double)map.tile_width)/TILE_SPRITE_WIDTH, WHITE);
		}
	}
}

void destroy_tilemap(tilemap* map) {
	free(map->tiles);
}
