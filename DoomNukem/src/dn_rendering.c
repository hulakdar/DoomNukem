#include "dn_rendering.h"
#include "dn_simple_drawing.h"
#include "dn_events.h"
#include "dn_io.h"
#include "dn.h"

static void vsync(void)
{
	const unsigned	current_ticks = SDL_GetTicks();
	unsigned		frame_time;
	t_game_state	*game_state;

	game_state = get_game_state();
	frame_time = current_ticks - game_state->last_time;
	if (frame_time < 16)
		WAIT(16 - frame_time);
	game_state->last_time = current_ticks;
	game_state->frame_time = frame_time;
}

void init_render_state(void)
{
	t_render_state *render_state;

	render_state = get_render_state();
	render_state->renderer =
		SDL_CreateRenderer(render_state->window, -1, SDL_RENDERER_ACCELERATED);
	//SDL_RenderSetLogicalSize(render_state->renderer, render_state->w, render_state->h);
	render_state->pixels = ft_memalloc(sizeof(int) * (render_state->w * render_state->h));
	render_state->back_buffer = SDL_CreateTexture(render_state->renderer,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, render_state->w, render_state->h);
}

void	draw_loop()
{
	static int i = 10;
	t_render_state *render_state = get_render_state();

	init_render_state();
	while (true)
	{
		t_simple_vline line = { i, 100, 200, 0xFFFF};
		draw_vline(RENDER_TARGET(*render_state), line);
		i++;

		SDL_UpdateTexture(render_state->back_buffer, NULL, render_state->pixels, render_state->w * 4);
		SDL_RenderCopy(render_state->renderer, render_state->back_buffer, NULL, NULL);
		SDL_RenderPresent(render_state->renderer);
		vsync();
	}
}

t_render_state * get_render_state(void)
{
	static t_render_state render_state;

	return &render_state;
}
