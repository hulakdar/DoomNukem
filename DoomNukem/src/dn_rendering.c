#include "dn_rendering.h"
#include "dn_io.h"

int init_render_state(t_render_state *renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1 ||
	!(renderer->window = SDL_CreateWindow("RT",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, renderer->w,
		renderer->h, SDL_WINDOW_FLAGS)) || !(renderer->renderer =
			SDL_CreateRenderer(renderer->window, -1, SDL_RENDERER_ACCELERATED)))
	{
		char message[] = "failed to initialize SDL";
		ERROR(message);
		return (1);
	}
	SDL_RenderSetLogicalSize(renderer->renderer, renderer->w, renderer->h);
	renderer->pixels = malloc(sizeof(int) * (renderer->w * renderer->h));
	return (0);
}
