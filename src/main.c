#include "../include/raylib.h"

#include "tilemap.h"
#include "defines.h"
#include "game_state.h"

#include <stdio.h>

int main() {
	game_state state;
	if(!init_game_state(&state)) {
		printf("ERROR: failed to initialize game state.\n");
	}
	return 0;
}
