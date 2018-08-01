#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include "dn_math.h"
#include "dn_rendering.h"

/* Numbers are arbitrary */
#define W 608
#define H 480

#define EYE_HEIGHT 6.f
#define DUCK_HEIGHT 2.5f
#define HEAD_MARGIN 1.f
#define KNEE_HEIGHT 2.f
#define HFOV (0.73f * H)
#define VFOV (.2f * H)

typedef struct	s_sector
{
	float		floor;
	float		ceil;
	unsigned	npoints;
	t_vec2		*vertex;
	char		*neighbors;
}				t_sector;

typedef struct	s_player
{
	t_vec3	position;
	t_vec3	velocity;
	float	angle;
	float	angle_sin;
	float	angle_cos;
	float	yaw;
	int		sector;
}				t_player;

typedef struct	s_game_state
{
	t_render_state	renderer;
	t_player		player;
	t_sector		*sectors;

}				t_game_state;

/* 
** Pretty self-explanatory.
*/
/* void draw_line_single_color(int x, int y1, int y2, int color); */