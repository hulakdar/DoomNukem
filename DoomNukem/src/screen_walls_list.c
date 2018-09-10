#include "screen_walls_list.h"

t_screen_wall* new_screen_wall( )
{
	t_screen_wall* result = (t_screen_wall*)malloc( sizeof( t_screen_wall ) );
	result->next = NULL;
	//result->prev = NULL;
	return result;
}

void add_screen_wall_by_head( t_screen_wall* head, t_screen_wall* new_wall )
{
	while ( head->next )
	{
		head = head->next;
	}
	head->next = new_wall;
	//new_wall->prev = head;
}

void free_screen_wall_list_by_head( t_screen_wall* head )
{
	t_screen_wall* next;
	do
	{
		next = head->next;
		free( head );
		head = next;
	} while ( next );
}

t_screen_wall* back_screen_wall_list_by_head( t_screen_wall* head )
{
	while ( head->next )
	{
		head = head->next;
	}
	return ( head );
}