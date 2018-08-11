#pragma once


typedef struct	s_simple_vline 
{
	int			x;
	int			y1;
	int			y2;
	int			color;
}				t_simple_vline;

void draw_vline(struct s_renderable *renderable, t_simple_vline line);