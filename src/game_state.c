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

	state->tileSprites[EMPTY] = LoadTexture("C:/polytopia_clone/sprites/tile cube.png");
	state->tileSprites[GRASS] = LoadTexture("C:/polytopia_clone/sprites/tile cube green.png");
	state->tileSprites[SELECTED] = LoadTexture("C:/polytopia_clone/sprites/square tile wireframe.png");


	if(state->tileSprites !=0) {
		return 1;
	}

	return 0;
}

void init_mouse_info(game_state* state) {
	vec2 zeroVector = {0,0};
	state->mouseInfo.screenCell = zeroVector;
	state->mouseInfo.offset     = zeroVector;
	state->mouseInfo.worldCell  = zeroVector;
}

int init_game_state(game_state* state) {
	
	//TODO: create the tilemap in here rather than in main

	vec2 origin = {10, -10};

	vec2 cameraStart = {0,0};
	state->camera = cameraStart;
	state->worldOrigin = origin;
	state->world = 0;

	state->tileSprites = malloc(sizeof(Texture2D) * NUM_TILE_TYPES);

	if(!load_art(state)) {
		printf("ERROR: failed to load art.\n");
		return 0;
	}

	init_mouse_info(state);

	return 1;
}

//TODO: have a destroy_game_state function that handles this and other things like destroying the tilemap (if
//it exists?)
void free_art(Texture2D* art) {
	free(art);
}

//TODO: change this to select_tile or smn and factor in camera.
//honestly just have game_state state* be the paramter at this point
void update_mouse_info(mouse_info* info, int tileWidth, int tileHeight, vec2 origin, vec2 camera) {
	vec2 mousePos;
	mousePos.x = GetMouseX() + camera.x;
	mousePos.y = GetMouseY() + camera.y;
	info->screenCell.x = (mousePos.x)/(tileWidth);
	info->screenCell.y = (mousePos.y)/(tileHeight);

	info->offset.x = (mousePos.x)%(tileWidth);
	info->offset.y = (mousePos.y)%(tileHeight);


	//calculate world cell

	info->worldCell.x = (info->screenCell.y - origin.y) + (info->screenCell.x - origin.x);
	info->worldCell.y = (info->screenCell.y - origin.y) - (info->screenCell.x - origin.x);

	if(info->offset.y < (int)((-(0.5)*info->offset.x) + tileHeight/2)) {
		//region 1
		info->worldCell.x--;
	}

	if(info->offset.y < (int)(((0.5)*info->offset.x) - tileHeight/2)) {
		//region 2
		info->worldCell.y--;
	}

	if(info->offset.y > (int)(((0.5)*info->offset.x) + tileHeight/2)) {
		//region 3
		info->worldCell.y++;
	}

	if(info->offset.y > (int)((-(0.5)*info->offset.x) + 3*(tileHeight/2))) {
		//region 4
		info->worldCell.x++;
	}


}

void zoom(tilemap* map, int outFlag, vec2 *camera, vec2 origin) {
	static double timeOfZoom = 0.0f;
	double timeSinceZoom = GetTime() - timeOfZoom;
	//TODO: put some sort of timer in here so you can control speed of zoom


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

void move_camera(game_state* state, int direction) {
	switch(direction) {
		case UP:
			state->camera.y-= CAMERA_SPEED;
			break;
		case DOWN:
			state->camera.y+= CAMERA_SPEED;
			break;
		case LEFT:
			state->camera.x-= CAMERA_SPEED;
			break;
		case RIGHT:
			state->camera.x+= CAMERA_SPEED;
			break;
		default:
			printf("ERROR: undefined direction used in move_camera function.\n");
			break;
	}
}
