#include "dn_rendering.h"
#include "dn_io.h"
#include "dn.h"
#include <stdio.h>

int create_window(int width, int height)
{
	const char		error_message[] = "failed to initialize SDL";
	t_render_state	*render_state;

	render_state = get_render_state();
	render_state->w = width;
	render_state->h = height;
	if (SDL_Init(SDL_INIT_VIDEO) == -1 ||
		!(render_state->window = SDL_CreateWindow("RT",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_FLAGS)))
	{
		DN_ERROR(error_message);
		return (1);
	}
	return (0);
}

void event_handler(void)
{
	const t_game_state *game_state = get_game_state();
	t_player *player = &game_state->player;
	SDL_Event e;

	while (1)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				const t_vec2 up = {0, -1.f};
				const t_vec2 front = rotate_vec2(cos(-player->angle), sin(-player->angle), up);

				if (e.key.keysym.sym == SDLK_LEFT)
					player->angle -= 0.1f;
				else if (e.key.keysym.sym == SDLK_RIGHT)
					player->angle += 0.1f;
				if (e.key.keysym.sym == SDLK_UP)
				{
					const t_vec2 player2d = { player->position.x, player->position.y };
					const t_vec2 new_pos = VEC2_ADD(player2d, front);

					player->position = (t_vec3){new_pos.x, new_pos.y, 0};
					//printf("%f %f\n", player->position.x, player->position.y);
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					const t_vec2 player2d = { player->position.x, player->position.y };
					const t_vec2 new_pos = VEC2_SUB(player2d, front);

					player->position = (t_vec3){new_pos.x, new_pos.y, 0};
					//printf("%f %f\n", player->position.x, player->position.y);
				}
			}
			if (e.type == SDL_QUIT)
				return;
		}
	}
}
