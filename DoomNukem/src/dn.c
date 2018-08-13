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

	sectors[ 0 ] = ( t_sector ) { 4, 0 };
	sectors[ 1 ] = ( t_sector ) { 4, 4 };

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