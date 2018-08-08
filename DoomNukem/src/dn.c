#include "dn.h"


int init_game_state(t_game_state *game_state)
{
	game_state->render_state.h = 480;
	game_state->render_state.w = 640;
	init_render_state(&game_state->render_state);
	return 0;
}

void game_loop(t_game_state *game_state)
{
	while (true)
		Sleep(2);
}
