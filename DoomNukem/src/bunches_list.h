#pragma once

#include "screen_walls_list.h"

typedef struct		s_bunch
{
	struct s_bunch*	next;
	struct s_bunch*	prev;
	t_screen_wall*	screen_walls_list;
}					t_bunch;

t_bunch*			new_bunch( );
void				add_bunch_by_head( t_bunch* head, t_bunch* new_bunch );
void				free_bunch_list_by_head( t_bunch* head );
t_bunch*			back_bunch_list_by_head( t_bunch* head );
void				swap_bunches_in_list( t_bunch* bunch1, t_bunch* bunch2 );