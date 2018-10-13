#include "dn_rendering.h"
#include "dn_io.h"

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
	SDL_Event e;

	while (1)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return;
		}
	}
}
