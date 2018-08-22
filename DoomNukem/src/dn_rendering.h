#pragma once

#include <SDL.h>
#undef main

#define SDL_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)
#define SDL_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED)

#define RENDER_TARGET(x) (t_renderable *)(&(x).pixels)

#define RENDER_TARGET_INTERFACE int *pixels;int w;int h

typedef struct	s_renderable
{
	RENDER_TARGET_INTERFACE;
}				t_renderable;

typedef struct	s_render_state
{
	RENDER_TARGET_INTERFACE;
	SDL_Renderer	*renderer;
	SDL_Texture		*back_buffer;
	SDL_Window		*window;
}				t_render_state;

void			init_render_state(void);
void			draw_loop(void);
t_render_state	*get_render_state(void);