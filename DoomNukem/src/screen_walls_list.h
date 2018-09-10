#pragma once

#include <stdlib.h>

typedef struct				s_screen_wall
{
	//struct s_screen_wall*	prev;
	struct s_screen_wall*	next;
	short					wall_number;
	short					x1;
	short					x2;
}							t_screen_wall;

t_screen_wall*				new_screen_wall( );
void						add_screen_wall_by_head( t_screen_wall* head, t_screen_wall* new_wall );
void						free_screen_wall_list_by_head( t_screen_wall* head );
t_screen_wall*				back_screen_wall_list_by_head( t_screen_wall* head );