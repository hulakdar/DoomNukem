#include "bunches_list.h"

t_bunch* new_bunch( )
{
	t_bunch* result = (t_bunch*)malloc( sizeof( t_bunch ) );
	result->next = NULL;
	result->prev = NULL;
	return result;
}

void add_bunch_by_head( t_bunch* head, t_bunch* new_bunch )
{
	while ( head->next )
	{
		head = head->next;
	}
	head->next = new_bunch;
	new_bunch->prev = head;
}

void free_bunch_list_by_head( t_bunch* head )
{
	t_bunch* next;
	do
	{
		free_screen_wall_list_by_head( head->screen_walls_list );
		next = head->next;
		free( head );
		head = next;
	} while ( next );
}

t_bunch* back_bunch_list_by_head( t_bunch* head )
{
	while ( head->next )
	{
		head = head->next;
	}
	return ( head );
}

void swap_bunches_in_list( t_bunch* bunch1, t_bunch* bunch2 )
{
	if ( bunch2->prev )
	{
		bunch2->prev->next = bunch1;
	}
	if ( bunch2->next )
	{
		bunch2->next->prev = bunch1;
	}
	if ( bunch1->prev )
	{
		bunch1->prev->next = bunch2;
	}
	if ( bunch1->next )
	{
		bunch1->next->prev = bunch2;
	}
}