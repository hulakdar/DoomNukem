#include "dn_render_helpers.h"
#include "dn.h"
#include "dn_events.h"

t_render_state *init_render_state(void)
{
	t_render_state *render_state;

	render_state = get_render_state();
	render_state->renderer =
		SDL_CreateRenderer(render_state->window, -1, SDL_RENDERER_ACCELERATED);
	//SDL_RenderSetLogicalSize(render_state->renderer, render_state->w, render_state->h);
	render_state->pixels = ft_memalloc(sizeof(t_color)
		* (render_state->w * render_state->h));
	render_state->depth_buffer = ft_memalloc(sizeof(float)
		* (render_state->w * render_state->h));
	render_state->screen_texture = SDL_CreateTexture(render_state->renderer,
		SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STREAMING,
		render_state->w, render_state->h);
	return render_state;
}

void vsync(void)
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

void end_render_frame(void)
{
	t_render_state *render_state;

	render_state = get_render_state();
	SDL_UpdateTexture(render_state->screen_texture, NULL, render_state->pixels, render_state->w * 3);
	SDL_RenderCopy(render_state->renderer, render_state->screen_texture, NULL, NULL);
	SDL_RenderPresent(render_state->renderer);
	vsync();
}

