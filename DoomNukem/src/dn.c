#include "dn.h"
#include "dn_events.h"

t_vec2 verts[] = {
	{0,0},
	{0,20},
	{30,30},
	{30,20},
	{20,0},
	{0,0}
};

t_sector sectors[] = 
{
	{0, 5, 9, 0},
	{0, 0, 0, 0}
};

t_map lol_map = {sectors, verts, NULL};

int init_game_state(void)
{
	t_game_state *game_state;

	game_state = get_game_state();
	game_state->current_map = &lol_map;
	return 0;
}

t_game_state *get_game_state(void)
{
	static t_game_state game_state;

	return &game_state;
}

void game_loop(void)
{
	//while (true)
		WAIT(16);
}
