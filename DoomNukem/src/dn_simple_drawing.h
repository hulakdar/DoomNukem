#pragma once

#include "dn_rendering.h"

typedef struct	s_item
{
	int			sector_number;
	int			sx1;
	int			sx2;
}				t_item;

typedef struct	s_simple_vline 
{
	int			x;
	int			y1;
	int			y2;
	t_color		color;
	float		depth;
}				t_simple_vline;

void	draw_vline(struct s_render_state *renderable, t_simple_vline line);
void	draw_screen_simple(void);
t_color make_color_from_int(int hex);