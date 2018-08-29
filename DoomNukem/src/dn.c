#include "dn.h"
#include "dn_events.h"

void initMapDataBase( t_game_state *game_state )
{
	t_vec4* points = (t_vec4*)malloc( 8 * sizeof( t_vec4 ) );
	t_wall* walls = (t_wall *)malloc( 8 * sizeof( t_wall ) );
	t_sector* sectors = (t_sector*)malloc( 2 * sizeof( t_sector ) );

	points[ 0 ] = ( t_vec4 ) { 0, 0, 0, 3 };
	points[ 1 ] = ( t_vec4 ) { 0, 10, 0, 3 };
	points[ 2 ] = ( t_vec4 ) { 10, 10, 0, 3 };
	points[ 3 ] = ( t_vec4 ) { 10, 0, 0, 3 };
	points[ 4 ] = ( t_vec4 ) { 4, 4, 1, 3 };
	points[ 5 ] = ( t_vec4 ) { 4, 6, 1, 3 };
	points[ 6 ] = ( t_vec4 ) { 6, 6, 1, 3 };
	points[ 7 ] = ( t_vec4 ) { 6, 4, 1, 3 };

	walls[ 0 ] = ( t_wall ) { 0, 1, -1 };
	walls[ 1 ] = ( t_wall ) { 1, 2, -1 };
	walls[ 2 ] = ( t_wall ) { 2, 3, -1 };
	walls[ 3 ] = ( t_wall ) { 3, 0, -1 };
	walls[ 4 ] = ( t_wall ) { 4, 5, 0 };
	walls[ 5 ] = ( t_wall ) { 5, 6, 0 };
	walls[ 6 ] = ( t_wall ) { 6, 7, 0 };
	walls[ 7 ] = ( t_wall ) { 7, 4, 0 };

	short* inside_sectors_number = (short*)malloc( sizeof( short ) );
	inside_sectors_number[ 0 ] = 1;
	sectors[ 0 ] = ( t_sector ) { 4, 0, inside_sectors_number, 1 };
	sectors[ 1 ] = ( t_sector ) { 4, 4, NULL, 0 };

	game_state->map_data.points_number = 8;
	game_state->map_data.walls_number = 8;
	game_state->map_data.sectors_number = 2;
	game_state->map_data.points = points;
	game_state->map_data.walls = walls;
	game_state->map_data.sectors = sectors;
}

int init_game_state( t_game_state *game_state )
{
	initMapDataBase( game_state );
	game_state->last_time = 0;
	game_state->frame_time = 0;
	game_state->render_state.h = 480;
	game_state->render_state.w = 640;
	init_render_state( &game_state->render_state );
	return 0;
}

void game_loop( t_game_state *game_state )
{
	while ( true )
		WAIT( 2 );
}

static bool is_in_array(short* array, short value, short size )
{
	do
	{
		if ( *array == value )
		{
			return true;
		}
		array++;
	} while ( --size );
}

static bool is_in_sector( float x, t_game_state* game_state, short sector_number )
{
	t_vec4* points = game_state->map_data.points;
	t_wall* walls = game_state->map_data.walls;
	t_sector* sector = &game_state->map_data.sectors[ sector_number ];
	short start_wall = sector->start_wall;
	short current_wall = start_wall;
	unsigned char intersections_count = 0;
	do
	{
		short x1 = points[ walls[ current_wall ].point1 ].x;
		short x2 = points[ walls[ walls[ current_wall ].next_wall ].point1 ].x;
		if ( (x > x1) && (x < x2) || ( x > x2 ) && ( x < x1 ) )
		{
			intersections_count++;
		}
		current_wall = walls[ current_wall ].next_wall;
	} while ( walls[current_wall].next_wall != start_wall );
	return intersections_count && !( intersections_count % 2 );
}

short update_sector( t_game_state *game_state, float x_player, short last_sector )
{
	if ( is_in_sector( x_player, game_state, last_sector ) )
	{
		return last_sector;
	}
	else
	{
		short visited_sectors[ MAX_WALLS_NUMBER ];
		short visited_sectors_count = 0;
		short start_wall = game_state->map_data.sectors[ last_sector ].start_wall;
		short current_wall = start_wall;
		do
		{
			short next_sector = game_state->map_data.walls[ current_wall ].next_sector;
			if ( next_sector != -1 )
			{
				if ( is_in_sector( x_player, game_state, next_sector ) )
				{
					return next_sector;
				}
				visited_sectors[ visited_sectors_count ] = next_sector;
				visited_sectors_count++;
			}
			current_wall = game_state->map_data.walls[ current_wall ].next_wall;
		} while ( game_state->map_data.walls[ current_wall ].next_wall != start_wall );

		short i = 0;
		while ( i < game_state->map_data.sectors_number )
		{
			if ( !is_in_array( visited_sectors, i, visited_sectors_count )
				&& is_in_sector( x_player, game_state, i ) )
			{
				return i;
			}
			i++;
		}
	}
}

bool is_in_front_of_wall( t_game_state *game_state, short wall_number )
{
	t_vec4* points = game_state->map_data.points;
	t_wall* walls = game_state->map_data.walls;
	t_vec3* player = &game_state->player.position;
	t_vec4* point1 = &points[ walls[ wall_number ].point1 ];
	t_vec4* point2 = &points[ walls[ walls[wall_number].next_wall ].point1 ];
	return ( ( point2->x - point1->x ) * ( player->y - point1->y ) - ( point2->y - point1->y ) * ( player->x - point1->x ) ) < 0;
}

static bool is_wall_in_fov( t_game_state *game_state, short wall_number )
{
	t_vec4* points = game_state->map_data.points;
	t_wall* walls = game_state->map_data.walls;
	t_vec2 left_point;
	t_vec2 right_point;
	
	left_point.x = points[ walls[ wall_number ].point1 ].x - game_state->player.position.x;
	left_point.y = points[ walls[ wall_number ].point1 ].y - game_state->player.position.y;

	right_point.x = points[ walls[ walls[ wall_number ].next_wall ].point1 ].x - game_state->player.position.x;
	right_point.y = points[ walls[ walls[ wall_number ].next_wall ].point1 ].y - game_state->player.position.y;

	if ( left_point.y <= 0.0f && right_point.y <= 0.0f )
		return false;

	if ( ( game_state->player.left_fov_edge.x * left_point.x + game_state->player.left_fov_edge.y * left_point.y > 0
		&& game_state->player.left_fov_edge.x * right_point.x + game_state->player.left_fov_edge.y * right_point.y > 0) ||
		( game_state->player.right_fov_edge.x * left_point.x + game_state->player.right_fov_edge.y * left_point.y < 0
			&& game_state->player.right_fov_edge.x * right_point.x + game_state->player.right_fov_edge.y * right_point.y < 0 ) )
		return false;

	if ( ( game_state->player.left_fov_edge.x * left_point.x + game_state->player.left_fov_edge.y * left_point.y > 0 )
		&& ( game_state->player.right_fov_edge.x * left_point.x + game_state->player.right_fov_edge.y * left_point.y < 0 )
		&& ( left_point.y < 0.0f ) )
		return false;

	if ( ( game_state->player.left_fov_edge.x * right_point.x + game_state->player.left_fov_edge.y * right_point.y > 0 )
		&& ( game_state->player.right_fov_edge.x * right_point.x + game_state->player.right_fov_edge.y * right_point.y < 0 )
		&& ( right_point.y < 0.0f ) )
		return false;

	return true;
}

static t_screen_wall get_screen_wall( t_game_state* game_state, short wall_number )
{
	t_screen_wall result;

	result.wall_number = wall_number;

	t_vec4* points = game_state->map_data.points;
	t_wall* walls = game_state->map_data.walls;
	t_vec2 left_point;
	t_vec2 right_point;

	left_point.x = points[ walls[ wall_number ].point1 ].x - game_state->player.position.x;
	left_point.y = points[ walls[ wall_number ].point1 ].y - game_state->player.position.y;

	right_point.x = points[ walls[ walls[ wall_number ].next_wall ].point1 ].x - game_state->player.position.x;
	right_point.y = points[ walls[ walls[ wall_number ].next_wall ].point1 ].y - game_state->player.position.y;

	left_point.x /= left_point.y;
	//left_point.y /= left_point.y;

	right_point.x /= right_point.y;
	//right_point.y /= right_point.y;

	result.x1 = ( left_point.x + game_state->player.right_fov_edge.x ) / 2.0f * W;
	result.x2 = ( right_point.x + game_state->player.right_fov_edge.x ) / 2.0f * W;


	return result;
}

void analize_sector( t_game_state *game_state, short sector_number )
{
	t_vec4* points = game_state->map_data.points;
	t_wall* walls = game_state->map_data.walls;
	t_sector* sector = &game_state->map_data.sectors[ sector_number ];
	short start_wall = sector->start_wall;
	short current_wall = start_wall;
	do
	{
		if ( is_in_front_of_wall( game_state, current_wall ) && is_wall_in_fov( game_state, current_wall ) )
		{
			if ( game_state->bunches )
			{

			}
			else
			{
				t_bunch bunch;
				t_screen_wall wall = get_screen_wall( game_state, current_wall );
				
			}
		}
		else
		{

		}
		current_wall = game_state->map_data.walls[ current_wall ].next_wall;
	} while ( walls[ current_wall ].next_wall != start_wall );
}