#include "dn.h"
#include "dn_events.h"

t_vec2 verts[] = {
	{0,0},
	{0,40},
	{10,60},
	{70,90},
	{80,80},
	{90,40},
	{50,0},
	{30,0},
	{0,0}
};

t_sector sectors[] = 
{
	{0, 5, 9, 0},
	{5, 3, 9, 0},
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
	t_game_state *game_state = get_game_state();

	while (true)
		WAIT(16);
}
