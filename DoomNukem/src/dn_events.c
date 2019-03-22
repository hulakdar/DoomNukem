#include "dn_rendering.h"
#include "dn_io.h"
#include "dn.h"
#include <stdio.h>

int create_window(int width, int height)
{
	const char		error_message[] = "failed to initialize SDL";
	t_render_state	*render_state;

	render_state = get_render_state();
	render_state->w = width * 2;
	render_state->h = height * 2;
	if (SDL_Init(SDL_INIT_VIDEO) == -1 ||
		!(render_state->window = SDL_CreateWindow("DNK",
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
	t_game_state *game_state = get_game_state();
	t_player *player = &game_state->player;
	SDL_Event e;

	while (1)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_LEFT)
					player->buttons.left = 1;
				else if (e.key.keysym.sym == SDLK_RIGHT)
					player->buttons.right = 1;
				else if (e.key.keysym.sym == SDLK_UP)
					player->buttons.up = 1;
				else if (e.key.keysym.sym == SDLK_DOWN)
					player->buttons.down = 1;
				else if (e.key.keysym.sym == SDLK_ESCAPE)
					return;
			}
			else if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_LEFT)
					player->buttons.left = 0;
				else if (e.key.keysym.sym == SDLK_RIGHT)
					player->buttons.right = 0;
				else if (e.key.keysym.sym == SDLK_UP)
					player->buttons.up = 0;
				else if (e.key.keysym.sym == SDLK_DOWN)
					player->buttons.down = 0;
			}
			if (e.type == SDL_QUIT)
				return;
		}
	}
}
