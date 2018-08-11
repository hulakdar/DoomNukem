#pragma once

#include <SDL.h>
#undef main

#define SDL_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)
#define SDL_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED)

#define RENDERABLE_INTERFACE int *pixels;int w;int h

typedef struct	s_renderable
{
	RENDERABLE_INTERFACE;
}				t_renderable;

typedef struct	s_render_state
{
	RENDERABLE_INTERFACE;
	SDL_Renderer	*renderer;
	SDL_Texture		*back_buffer;
	SDL_Window		*window;
}				t_render_state;

int				init_render_state(t_render_state *renderer);
void			draw_loop(struct s_game_state *game_state);