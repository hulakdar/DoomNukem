#pragma once

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
	int			color;
}				t_simple_vline;

void	draw_vline( struct s_renderable *renderable, t_simple_vline line );
void	draw_screen_simple( struct s_game_state *game_state );