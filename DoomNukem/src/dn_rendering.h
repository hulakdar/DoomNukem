#pragma once

#include <SDL.h>
#undef main

#define SDL_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)
#define SDL_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED)

typedef struct	s_render_state
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				*pixels;
	int				w;
	int				h;
}				t_render_state;

int				init_render_state(t_render_state *renderer);