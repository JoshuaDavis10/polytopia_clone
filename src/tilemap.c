#include "../include/raylib.h"

#include "tilemap.h"

int create_tilemap(tilemap* map, vec2 mapsize) {
	map->mapsize = mapsize;
	map->tiles = malloc(sizeof(int) * (mapsize.x * mapsize.y));
	for(int i = 0; i < (mapsize.x * mapsize.y); i++) {
		map->tiles[i] = 0;
	}
	return 1;
}

void draw_tilemap(tilemap tilemap, vec2 center, Texture2D* sprites) {
	
}

int delete_tilemap(tilemap* map) {
	free(map->tiles);
}
