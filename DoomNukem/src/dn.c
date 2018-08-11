#include "dn.h"
#include "dn_events.h"

int init_game_state(t_game_state *game_state)
{
	game_state->last_time = 0;
	game_state->frame_time = 0;
	game_state->render_state.h = 480;
	game_state->render_state.w = 640;
	init_render_state(&game_state->render_state);
	return 0;
}

void game_loop(t_game_state *game_state)
{
	while (true)
		WAIT(2);
}
