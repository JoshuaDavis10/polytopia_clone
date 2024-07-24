#include "user_interface.h"

#include <stdio.h>

int draw_menu_screen(game_state* state) {

	vec2 mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

		//new game case
		if((mouse.x < WINDOW_WIDTH/2  + BUTTON_WIDTH/2)  && (mouse.x > WINDOW_WIDTH/2 - BUTTON_WIDTH/2) &&
	       (mouse.y < WINDOW_HEIGHT/2 + BUTTON_HEIGHT/2) && (mouse.y > WINDOW_HEIGHT/2 - BUTTON_HEIGHT/2)) {

			state->menuFlag = 0;
			vec2 size = {11, 11};

			load_tilemap_random(state->world, size);
		}

		//resume game case
		if((mouse.x < WINDOW_WIDTH/2    + BUTTON_WIDTH/2)  && (mouse.x > WINDOW_WIDTH/2    - BUTTON_WIDTH/2) &&
	   	   (mouse.y < 2*WINDOW_HEIGHT/3 + BUTTON_HEIGHT/2) && (mouse.y > 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/2)) {

			state->menuFlag = 0;

			if(!load_tilemap_from_file(state->world, "tilemaps/tilemap.txt")) {
				printf("Failed to load file: tilemaps/tilemap.txt.\n");
				return 0;
			}
		}
	}

	//mouse is over new game button
	if((mouse.x < WINDOW_WIDTH/2  + BUTTON_WIDTH/2)  && (mouse.x > WINDOW_WIDTH/2 - BUTTON_WIDTH/2) &&
	   (mouse.y < WINDOW_HEIGHT/2 + BUTTON_HEIGHT/2) && (mouse.y > WINDOW_HEIGHT/2 - BUTTON_HEIGHT/2)) {

		BeginDrawing();

		ClearBackground(BLACK);
		DrawRectangle(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT/2 - BUTTON_HEIGHT/2, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE);
		DrawText("NEW GAME", WINDOW_WIDTH/2 - BUTTON_WIDTH/2 + 20, WINDOW_HEIGHT/2 - BUTTON_HEIGHT/4, BUTTON_HEIGHT/2, BLACK);
		DrawRectangle(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/2, BUTTON_WIDTH, BUTTON_HEIGHT, BLUE);
		DrawText("RESUME GAME", WINDOW_WIDTH/2 - BUTTON_WIDTH/2 + 5, 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/4, BUTTON_HEIGHT/2, WHITE);

		EndDrawing();
	}

	//mouse is over resume game button
	else if((mouse.x < WINDOW_WIDTH/2    + BUTTON_WIDTH/2)  && (mouse.x > WINDOW_WIDTH/2    - BUTTON_WIDTH/2) &&
	   (mouse.y < 2*WINDOW_HEIGHT/3 + BUTTON_HEIGHT/2) && (mouse.y > 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/2)) {
		
		BeginDrawing();

		ClearBackground(BLACK);
		DrawRectangle(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT/2 - BUTTON_HEIGHT/2, BUTTON_WIDTH, BUTTON_HEIGHT, BLUE);
		DrawText("NEW GAME", WINDOW_WIDTH/2 - BUTTON_WIDTH/2 + 20, WINDOW_HEIGHT/2 - BUTTON_HEIGHT/4, BUTTON_HEIGHT/2, WHITE);
		DrawRectangle(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/2, BUTTON_WIDTH, BUTTON_HEIGHT, WHITE);
		DrawText("RESUME GAME", WINDOW_WIDTH/2 - BUTTON_WIDTH/2 + 5, 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/4, BUTTON_HEIGHT/2, BLACK);

		EndDrawing();
	}

	else {

		//draw stuff
		BeginDrawing();

		ClearBackground(BLACK);
		DrawRectangle(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT/2 - BUTTON_HEIGHT/2, BUTTON_WIDTH, BUTTON_HEIGHT, BLUE);
		DrawText("NEW GAME", WINDOW_WIDTH/2 - BUTTON_WIDTH/2 + 20, WINDOW_HEIGHT/2 - BUTTON_HEIGHT/4, BUTTON_HEIGHT/2, WHITE);
		DrawRectangle(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/2, BUTTON_WIDTH, BUTTON_HEIGHT, BLUE);
		DrawText("RESUME GAME", WINDOW_WIDTH/2 - BUTTON_WIDTH/2 + 5, 2*WINDOW_HEIGHT/3 - BUTTON_HEIGHT/4, BUTTON_HEIGHT/2, WHITE);

		EndDrawing();
	}

	return 1;
}

void draw_game_UI(game_state* state) {

	int tiletype = state->world->tiles[state->selectedTile.y*(state->world->mapsize.y) + state->selectedTile.x];
	char* msg;

	//UI rectangle thing at bottom of screen
	//TODO: how to make it transparent like polytopia does?
	Vector2 spritePos = {WINDOW_WIDTH/20, 17*WINDOW_HEIGHT/20};
	DrawRectangle(0, 4*WINDOW_HEIGHT/5, WINDOW_WIDTH, WINDOW_HEIGHT/5, DARKGRAY);

	//draw image of selected tile in ui + name of tile type
	DrawTextureEx(state->tileSprites[tiletype], spritePos, 0.0f, 2.0f, WHITE);
	switch(tiletype) {
		case FIELD:
			msg = "Field";
			break;
		case FOREST:
			msg = "Forest";
			break;
		case MOUNTAIN:
			msg = "Mountain";
			break;
		case WATER:
			msg = "Water";
			break;
		case OCEAN:
			msg = "Ocean";
			break;
		case VILLAGE:
			msg = "Village";
			break;
		default:
			msg = "ERROR: invalid tile type.";
			break;
	}
	DrawText(msg, WINDOW_WIDTH/10, 17*WINDOW_HEIGHT/20, 20, WHITE);

	//'X' button
	//TODO: make it a sprite and position it better etc...
	DrawCircle(9*WINDOW_WIDTH/10, 9*WINDOW_HEIGHT/10, WINDOW_WIDTH/40, WHITE);
	Vector2 start1 = {9*WINDOW_WIDTH/10 - WINDOW_WIDTH/80, 9*WINDOW_HEIGHT/10 - WINDOW_WIDTH/80};
	Vector2 end1 = {9*WINDOW_WIDTH/10 + WINDOW_WIDTH/80, 9*WINDOW_HEIGHT/10 + WINDOW_WIDTH/80};
	Vector2 start2 = {9*WINDOW_WIDTH/10 - WINDOW_WIDTH/80, 9*WINDOW_HEIGHT/10 + WINDOW_WIDTH/80};
	Vector2 end2 = {9*WINDOW_WIDTH/10 + WINDOW_WIDTH/80, 9*WINDOW_HEIGHT/10 - WINDOW_WIDTH/80};

	DrawLineBezier(start1, end1, 5.0f, BLACK);
	DrawLineBezier(start2, end2, 5.0f, BLACK);
	
}
