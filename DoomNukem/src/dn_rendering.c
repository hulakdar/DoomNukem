#include "dn_rendering.h"
#include "dn_io.h"
#include "dn.h"

void init_renderer( t_render_state *render_state )
{
	render_state->renderer =
		SDL_CreateRenderer( render_state->window, -1, SDL_RENDERER_ACCELERATED );
	SDL_RenderSetLogicalSize( render_state->renderer, render_state->w, render_state->h );
	render_state->pixels = malloc( sizeof( int ) * ( render_state->w * render_state->h ) );
}

int init_render_state(t_render_state *renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1 ||
		!(renderer->window = SDL_CreateWindow("RT",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, renderer->w,
		renderer->h, SDL_WINDOW_FLAGS)))
	{
		char message[] = "failed to initialize SDL";
		ERROR(message);
		return (1);
	}
	else
	{
		init_renderer( renderer );
	}
	return (0);
}

void	draw_loop(struct s_game_state *game_state)
{
	while (true)
	{
		SDL_Renderer *renderer = game_state->render_state.renderer;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
		SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
		SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
		SDL_RenderPresent(game_state->render_state.renderer);
	}
}
