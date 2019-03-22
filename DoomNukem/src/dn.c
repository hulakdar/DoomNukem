#include "dn.h"
#include "dn_events.h"

t_vec2 verts[] = {
	{-10,-10},
	{-10,40},
	{10,60},
	{70,90},
	{80,80},
	{90,40},
	{50,10},
	{30,-20},
	{-10,-10}
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
	game_state->player.speed = 10.f;
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
	t_game_state	*game_state = get_game_state();
	t_player		*player = &game_state->player;
	float			delta_time = 0.1f;
	unsigned int	start_time = SDL_GetTicks();

	while (true)
	{
		const t_vec2 up = { 0, -delta_time * player->speed };
		const t_vec2 front = rotate_vec2(cosf(-player->angle), sinf(-player->angle), up);
		const t_vec2 player2d = { player->position.x, player->position.y };

		if (player->buttons.up)
		{
			const t_vec2 new_pos = VEC2_ADD(player2d, front);

			player->position = (t_vec3) { new_pos.x, new_pos.y, 0 };
			//printf("%f %f\n", player->position.x, player->position.y);
		}
		else if (player->buttons.down)
		{
			const t_vec2 new_pos = VEC2_SUB(player2d, front);

			player->position = (t_vec3) { new_pos.x, new_pos.y, 0 };
			//printf("%f %f\n", player->position.x, player->position.y);
		}
		if (player->buttons.left)
			player->angle -= delta_time;
		else if (player->buttons.right)
			player->angle += delta_time;

		unsigned int end_time = SDL_GetTicks();
		delta_time = (end_time - start_time) / 1000.f;
		start_time = end_time;
	}
}
