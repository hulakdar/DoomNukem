#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include "dn_math.h"
#include "dn_rendering.h"
#include "libft.h"

/* Numbers are arbitrary */
#define W 608
#define H 480

#define EYE_HEIGHT 6.f
#define DUCK_HEIGHT 2.5f
#define HEAD_MARGIN 1.f
#define KNEE_HEIGHT 2.f
#define HFOV (0.73f * H)
#define VFOV (.2f * H)
#define MAX_WALLS_NUMBER 10

/*
** DISCLAIMER:
**	Wherever you see t_vector and want to do something with it,
** please, use it with caution. It's better to do everything in
** a separate function and pass a copy (not a pointer) of the
** s_vector struct.
**
**	If not sure how to use it, ask skamoza for clarification.
**
**	If someone has an idea how to implement it in C with static
** type-checking and within Norm constraints let me know.
*/

/*
**	One sector of the map. Should be convex(!!!)
*/
typedef struct		s_wall
{
	short			point1;
	short			next_wall;
	short			next_sector;
}					t_wall;

typedef struct	s_sector
{
	char			wall_number;
	short			start_wall;
}					t_sector;

typedef struct	s_map
{
	t_vector	sectors;
	t_vector	walls;
}				t_map;

typedef struct	s_player
{
	t_vec3		position;
	t_vec3		velocity;
	float		angle;
	float		angle_sin;
	float		angle_cos;
	float		yaw;
	int			sector;
}				t_player;

/*
**	Structure to contain everything you need to hold
** through the entire lifetime of the application.
*/

typedef struct	s_map_data_base
{
	short			points_number;
	short			walls_number;
	short			sectors_number;
	t_vec4*			points;
	t_wall*			walls;
	t_sector*		sectors;
}					t_map_data_base;

typedef struct		s_game_state
{
	t_render_state	render_state;
	t_player		player;
	t_map_data_base	map_data;
	unsigned int	last_time;
	unsigned int	frame_time;
}					t_game_state;


/* 
** Pretty self-explanatory.
*/
int				init_game_state(t_game_state *game_state);

void			game_loop(t_game_state *game_state);

short update_sector( t_game_state *game_state, float x_player, short last_sector );

bool is_in_array( short* array, short value, short size );