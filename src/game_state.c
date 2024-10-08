#include "../include/raylib.h"

#include "game_state.h"
#include "tilemap.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_ZOOM_FACTOR 9 
#define ZOOM_SPEED 0.02f
#define CAMERA_SPEED 4 


int load_art(game_state* state) {

	state->tileSprites[FIELD] = LoadTexture("C:/polytopia_clone/sprites/tile cube green.png");
	state->tileSprites[FOREST] = LoadTexture("C:/polytopia_clone/sprites/forest cube.png");
	state->tileSprites[MOUNTAIN] = LoadTexture("C:/polytopia_clone/sprites/mountain cube.png");
	state->tileSprites[WATER] = LoadTexture("C:/polytopia_clone/sprites/water cube.png");
	state->tileSprites[OCEAN] = LoadTexture("C:/polytopia_clone/sprites/ocean cube.png");
	state->tileSprites[VILLAGE] = LoadTexture("C:/polytopia_clone/sprites/village cube.png");
	state->tileSprites[SELECTED] = LoadTexture("C:/polytopia_clone/sprites/square tile wireframe.png");

	return 1;
}


int init_game_state(game_state* state, tilemap* world) {
	
	//camera and origin
	vec2 origin = {5, 0};
	vec2 cameraStart = {0,0};
	vec2 mouseInitial = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
	state->camera = cameraStart;
	state->mousePosPrev = mouseInitial;
	state->worldOrigin = origin;

	//tilemap
	state->world = world;

	if(!load_tilemap_from_file(world, "tilemaps/tilemap.txt")) {
		printf("Failed to load file: tilemaps/tilemap.txt.\n");
		return 0;
	}

	vec2 initialSelectedTile = {-1, -1};
	state->selectedTile = initialSelectedTile; //selectedTile of -1 means no tile is selected

	//tile art
	state->tileSprites = malloc(sizeof(Texture2D) * NUM_TILE_TYPES);
	load_art(state);

	return 1;
}


//destroy game state (i.e. free all dynamically allocated memory)
void destroy_game_state(game_state* state) {
	free(state->tileSprites);
	destroy_tilemap(state->world);
}

//TODO: don't let a tile be selected if it overlaps with the UI
void select_tile(game_state* state) {
	vec2 mousePos;
	vec2 worldCell;
	vec2 screenCell;
	vec2 offset;
	mousePos.x = GetMouseX() + state->camera.x;
	mousePos.y = GetMouseY() + state->camera.y;
	screenCell.x = (mousePos.x)/(state->world->tile_width);
	screenCell.y = (mousePos.y)/(state->world->tile_height);

	offset.x = (mousePos.x)%(state->world->tile_width);
	offset.y = (mousePos.y)%(state->world->tile_height);


	//calculate world cell

	worldCell.x = (screenCell.y - state->worldOrigin.y) + (screenCell.x - state->worldOrigin.x);
	worldCell.y = (screenCell.y - state->worldOrigin.y) - (screenCell.x - state->worldOrigin.x);

	if(offset.y < (int)((-(0.5)*offset.x) + state->world->tile_height/2)) {
		//region 1
		worldCell.x--;
	}

	if(offset.y < (int)(((0.5)*offset.x) - state->world->tile_height/2)) {
		//region 2
		worldCell.y--;
	}

	if(offset.y > (int)(((0.5)*offset.x) + state->world->tile_height/2)) {
		//region 3
		worldCell.y++;
	}

	if(offset.y > (int)((-(0.5)*offset.x) + 3*(state->world->tile_height/2))) {
		//region 4
		worldCell.x++;
	}

	if(worldCell.x < 0 || worldCell.x >= state->world->mapsize.x || worldCell.y < 0 || worldCell.y >= state->world->mapsize.y) {
		//state->selectedTile.x = -1;
		//state->selectedTile.y = -1;
	}
	else {
		state->selectedTile.x = worldCell.x;
		state->selectedTile.y = worldCell.y;
	}
}


void draw_selected_tile(game_state* state) {

	if(state->selectedTile.x < 0 || state->selectedTile.y < 0) {
		return;
	}

	//calculate screen coordinates
	Vector2 screenCoords;
	screenCoords.x = (state->worldOrigin.x * state->world->tile_width)  + ((state->selectedTile.x-state->selectedTile.y) * (state->world->tile_width/2)) - state->camera.x;
	screenCoords.y = (state->worldOrigin.y * state->world->tile_height) + ((state->selectedTile.x+state->selectedTile.y) * (state->world->tile_height/2)) - state->camera.y;

	//draw
	DrawTextureEx(state->tileSprites[SELECTED], screenCoords, 0.0f, ((double)state->world->tile_width)/TILE_SPRITE_WIDTH, WHITE);
}


//TODO: weird bug happens when zooming in or out where it kinda snaps to a tile rather than zooming to the legit center location...
void zoom(tilemap* map, int outFlag, vec2 *camera, vec2 origin) {

	static double timeOfZoom = 0.0f;
	double timeSinceZoom = GetTime() - timeOfZoom;

	if(timeSinceZoom > ZOOM_SPEED) {

		vec2 centerWorldPos;
		vec2 centerCell;
		vec2 centerOffset;
		centerWorldPos.x = WINDOW_WIDTH /2 + camera->x;
		centerWorldPos.y = WINDOW_HEIGHT/2 + camera->y;

		centerCell.x   = centerWorldPos.x / map->tile_width;
		centerCell.y   = centerWorldPos.y / map->tile_height;
		centerOffset.x = centerWorldPos.x % map->tile_width;
		centerOffset.y = centerWorldPos.y % map->tile_height;

		int zoomFactor = (int) ((double)map->tile_width)/TILE_SPRITE_WIDTH;

		if(outFlag) {
			if(map->tile_width > TILE_SPRITE_WIDTH) {

				//4 and 2 avoid an odd number problem that makes things misaligned... I think haha
				map->tile_width  -= 4*zoomFactor;
				map->tile_height -= 2*zoomFactor;

				centerWorldPos.x = centerCell.x * map->tile_width  + centerOffset.x - (int) (((double)centerOffset.x)/map->tile_width * zoomFactor);
				centerWorldPos.y = centerCell.y * map->tile_height + centerOffset.y - (int) (((double)centerOffset.y)/map->tile_width * zoomFactor);

	
				camera->x = centerWorldPos.x - WINDOW_WIDTH /2;
				camera->y = centerWorldPos.y - WINDOW_HEIGHT/2;

				timeOfZoom = GetTime();

			}
		}
		else {
			if(map->tile_width < TILE_SPRITE_WIDTH * MAX_ZOOM_FACTOR) {

				//4 and 2 avoid an odd number problem that makes things misaligned... I think haha
				map->tile_width  += 4*zoomFactor;
				map->tile_height += 2*zoomFactor;

				centerWorldPos.x = centerCell.x * map->tile_width  + centerOffset.x + (int) (((double)centerOffset.x)/map->tile_width * zoomFactor);
				centerWorldPos.y = centerCell.y * map->tile_height + centerOffset.y + (int) (((double)centerOffset.y)/map->tile_width * zoomFactor);

				camera->x = centerWorldPos.x - WINDOW_WIDTH /2;
				camera->y = centerWorldPos.y - WINDOW_HEIGHT/2;

				timeOfZoom = GetTime();

			}
		}

	}
}

//TODO: don't let camera go "out of bounds"
void move_camera(game_state* state) {
	
	vec2 move;
	move.x = state->mousePosPrev.x - GetMouseX();
	move.y = state->mousePosPrev.y - GetMouseY();

	state->camera.x += move.x;
	state->camera.y += move.y;

	state->mousePosPrev.x = GetMouseX();
	state->mousePosPrev.y = GetMouseY();
}
