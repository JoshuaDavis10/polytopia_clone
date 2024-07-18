#include "../include/raylib.h"

#include "input.h"

#include <stdio.h>

int process_input(game_state* state) {
	if(IsKeyDown(KEY_A)) {
		if(!move_camera(state, KEY_A)) {
			printf("ERROR: Failed to move camera when pressing key: 'a.'\n");
			return 0;
		}
	}
	if(IsKeyDown(KEY_W)) {
		if(!move_camera(state, KEY_W)) {
			printf("ERROR: Failed to move camera when pressing key: 'w.'\n");
			return 0;
		}
	}
	if(IsKeyDown(KEY_S)) {
		if(!move_camera(state, KEY_S)) {
			printf("ERROR: Failed to move camera when pressing key: 's.'\n");
			return 0;
		}
	}
	if(IsKeyDown(KEY_D)) {
		if(!move_camera(state, KEY_D)) {
			printf("ERROR: Failed to move camera when pressing key: 'd.'\n");
			return 0;
		}
	}

	if(IsKeyDown(KEY_Q)) {
		//TODO: create an enum for the 2nd parameter as like a 'zoomFlag' or something so that you're not just passing 1's or 0's
		if(!zoom_camera(state, 1)) {
			printf("ERROR: Failed to zoom camera out when pressing key: 'q.'\n");
			return 0;
		}
	}
	if(IsKeyDown(KEY_E)) {
		//TODO: create an enum for the 2nd parameter as like a 'zoomFlag' or something so that you're not just passing 1's or 0's
		if(!zoom_camera(state, 0)) {
			printf("ERROR: Failed to zoom camera out when pressing key: 'e.'\n");
			return 0;
		}
	}

	return 1;
}
