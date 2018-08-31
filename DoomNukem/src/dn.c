#include "dn.h"
#include "dn_events.h"

int init_game_state(void)
{
	t_game_state *game_state;

	game_state = get_game_state();
	game_state->last_time = 0;
	game_state->frame_time = 0;
	return 0;
}

t_game_state *get_game_state(void)
{
	static t_game_state game_state;

	return &game_state;
}

void game_loop(void)
{
	while (true)
		WAIT(2);
}
