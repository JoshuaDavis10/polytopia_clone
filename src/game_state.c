#include "game_state.h"

int init_game_state(game_state* state) {

	state->world = 0;

	state->mousePos = {0,0};
	state->mouseScreenCell = {0,0};
	state->mouseOffset = {0,0};
	state->mouseWorldCell = {0,0};
	return 1;
}
