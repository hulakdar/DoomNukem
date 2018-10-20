#pragma once

#include <SDL.h>
#undef main

#define SDL_WINDOW_FLAGS (SDL_WINDOW_RESIZABLE)
#define SDL_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED)
#define COLOR_BLACK ((t_color){0,0,0})
#define COLOR_WHITE ((t_color){255,255,255})
#define COLOR_RED ((t_color){255,0,0})
#define COLOR_GREEN ((t_color){0,255,0})
#define COLOR_BLUE ((t_color){0,0,255})

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct	s_render_state
{
	float			*depth_buffer;
	SDL_Renderer	*renderer;
	SDL_Texture		*screen_texture;
	SDL_Window		*window;
	t_color			*pixels;
	int				w;
	int				h;
}				t_render_state;

void			draw_loop(void);
t_render_state	*get_render_state(void);