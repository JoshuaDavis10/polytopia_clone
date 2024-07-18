#include "../include/raylib.h"

#include "tilemap.h"
#include "files.h"

#include <stdlib.h>
#include <string.h>

int add_tile(tilemap* tilemap, int tileNum, tile_type tileType) {
	tile addTile;
	addTile.type = tileType;

	vec2 firstTilePos = {0.0f, - (double)(0.5f * tilemap->height * tilemap->tile_height)};

	//TODO: have more configurable way to determine locations of tiles. Also so that the locations are relative to center of screen.
	int tileCol = tileNum % tilemap->width;
	int tileRow = tileNum / tilemap->width;
	addTile.position.x = firstTilePos.x + (tileCol * tilemap->tile_width/2) - (tileRow * tilemap->tile_width/2);
	addTile.position.y = firstTilePos.y + (tileCol * tilemap->tile_height/2) + (tileRow * tilemap->tile_height/2);

	
	tilemap->tiles[tileNum] = addTile; 

	//TODO: there should be some fail case where we return 0 (?). e.g. check if tileNum is greater than tilemap->width*tilemap->height
	//		or if tileType is even valid
	return 1;
}

//TODO: test more
int load_tilemap_from_file(tilemap* tilemap, const char* path) {

	//initialize file struct to be used
	file tilemapFile;
	tilemapFile.handle = 0;

	//open tilemap file
	if(!open_file(path, &tilemapFile, "r")) {
		printf("Failed to open file: %s. Terminating tilemap initialization.\n", path);
		return 0;
	}

	//determine width/height/tile size and allocate memory for tiles
	tilemap->tile_width = 200.0f;
	tilemap->tile_height = 100.0f;
	tilemap->width = atoi(read_line(&tilemapFile));
	tilemap->height = atoi(read_line(&tilemapFile));
	tilemap->tiles = malloc(sizeof(tile) * (tilemap->width * tilemap->height));

	//add all tiles
	tile_type currTileType;
	int currTile = 0;
	while(currTile < tilemap->width*tilemap->height) {
		//TODO: check that read_line was successful (just error check. It should always work but just like yk)
		currTileType = atoi(read_line(&tilemapFile));
		if(!add_tile(tilemap, currTile, currTileType)) {
			printf("Failed to add tile %d to tilemap. Terminating tilemap initialization.\n", currTile);
			return 0;
		}
		currTile++;
	}

	if(!close_file(&tilemapFile)) {
		printf("Failed to close file. Terminating tilemap initialization. \n");
		return 0;
	}
	
	return 1;
}

//generate a random tilemap with the given width and height parameters
int load_tilemap_random(tilemap* tilemap, int width, int height) {
	tilemap->tile_width = 200.0f;
	tilemap->tile_height = 100.0f;
	tilemap->width = width;
	tilemap->height = height;
	tilemap->tiles = malloc(sizeof(tile) * (tilemap->width * tilemap->height));

	int counter = 0;
	int tiletype;
	int randNum;
	while(counter < tilemap->width*tilemap->height) {

		tiletype = -1;

		//determine tile type
		randNum = rand() % 100;
		if(randNum < FRUIT_THRESHOLD) {
			tiletype = FRUIT;
		} else if (randNum >= FRUIT_THRESHOLD && randNum < CROP_THRESHOLD) {
			tiletype = CROP;
		} else if (randNum >= CROP_THRESHOLD && randNum < FIELD_THRESHOLD) {
			tiletype = FIELD;
		} else if (randNum >= FIELD_THRESHOLD && randNum < ANIMAL_THRESHOLD) {
			tiletype = ANIMAL;
		} else if (randNum >= ANIMAL_THRESHOLD && randNum < FOREST_THRESHOLD) {
			tiletype = FOREST;
		} else if (randNum >= FOREST_THRESHOLD && randNum < MOUNTAIN_THRESHOLD) {
			tiletype = MOUNTAIN;
		} else if (randNum >= MOUNTAIN_THRESHOLD && randNum < METAL_THRESHOLD) {
			tiletype = METAL;
		}

		if(!add_tile(tilemap, counter, tiletype)) {
			printf("Failed to add tile %d to tilemap. Terminating tilemap initialization.\n", counter);
			return 0;
		}

		counter++;

	}

	return 1;
}

//TODO: shouldn't pass pointer cuz that could change the tilemap on accident?
//TODO: test this function some more
int write_tilemap_to_file(tilemap* tilemap, const char* path) {

	//initialize new file struct to be used
	file tilemapFile;
	tilemapFile.handle = 0;

	//open new tilemap file
	if(!open_file(path, &tilemapFile, "w")) {
		printf("Failed to open file: %s. Terminating tilemap initialization.\n", path);
		return 0;
	}

	//write width/height to new tilemap file 

		//width
	char temp[100];
	if(snprintf(temp, 100, "%d", tilemap->width) < 0) {
		printf("snprintf failed\n");
	}
	const char* width = temp;

	//TODO: error check this write line
	write_line(&tilemapFile, width);


		//height
	if(snprintf(temp, 100, "%d", tilemap->height) < 0) {
		printf("snprintf failed\n");
	}
	const char* height = temp;

	//TODO: error check this write line
	write_line(&tilemapFile, height);

	//write tiles types to file
	for(int i = 0; i < tilemap->width*tilemap->height; i++) {
		if(snprintf(temp, 100, "%d", tilemap->tiles[i].type) < 0) {
			printf("snprintf failed\n");
		}
		const char* tileType = temp;
		write_line(&tilemapFile, tileType);
	}

	if(!close_file(&tilemapFile)) {
		printf("Failed to close file. Terminating writing of tilemap to file. \n");
		return 0;
	}

	return 1;
}

int destroy_tilemap(tilemap* tilemap) {
	//TODO: check for fail case (i.e. check return value of free (?))
	free(tilemap->tiles);
	return 1;
}

void draw_tilemap(tilemap tilemap, vec2 center, Texture2D* sprites) {
	int counter = 0;
	while(counter < tilemap.width * tilemap.height) {
		draw_tile(tilemap.tiles[counter], tilemap.tile_width, tilemap.tile_height, center, sprites);
		counter++;
	}
}

void draw_tile(tile tile, int tile_width, int tile_height, vec2 center, Texture2D* sprites) {

	//TODO: the 200.0f and 100.0f really need to not be hardcoded. I wonder if tile_width needs to be changed to like some ratio. idk
	vec2 centeredTilePos = {(tile_width/200.0f)*(tile.position.x) + center.x - tile_width/2, (tile_height/100.0f)*(tile.position.y) + center.y - tile_height/2};

	Vector2 tileDrawPos = {centeredTilePos.x, centeredTilePos.y};

	switch(tile.type) {
		case FRUIT:
			DrawTextureEx(sprites[FRUIT], tileDrawPos, 0.0f, (double)tile_width/50, RED);
			break;
		case CROP:
			DrawTextureEx(sprites[CROP], tileDrawPos, 0.0f, (double)tile_width/50, ORANGE);
			break;
		case FIELD:
			DrawTextureEx(sprites[FIELD], tileDrawPos, 0.0f, (double)tile_width/50, GREEN);
			break;
		case ANIMAL:
			DrawTextureEx(sprites[ANIMAL], tileDrawPos, 0.0f, (double)tile_width/50, BROWN);
			break;
		case FOREST:
			DrawTextureEx(sprites[FOREST], tileDrawPos, 0.0f, (double)tile_width/50, DARKGREEN);
			break;
		case MOUNTAIN:
			DrawTextureEx(sprites[MOUNTAIN], tileDrawPos, 0.0f, (double)tile_width/50, WHITE);
			break;
		case METAL:
			DrawTextureEx(sprites[METAL], tileDrawPos, 0.0f, (double)tile_width/50, YELLOW);
			break;
		default:
			printf("WARNING: Attempted to draw tile with unknown tile type.\n");
			break;
	}
}
