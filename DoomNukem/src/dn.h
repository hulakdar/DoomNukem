#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#undef main

/* Numbers are arbitrary */
#define W 608
#define H 480

#define EYE_HEIGHT 6
#define DUCK_HEIGHT 2.5f
#define HEAD_MARGIN 1
#define KNEE_HEIGHT 2
#define HFOV (0.73f * H)
#define VFOV (.2f * H)

/* Math "templated" macros */
#define CLAMP(a, mi, ma)  min(max(a, mi), ma)
#define CROSS(a0, a1, b0, b1) ((a0) * (b1) - (a1) * (b0))

/* Helper macro. Hate norm */
#define LESS(a0, a1, b0, b1) (MIN(a0, a1) <= MAX(b0, b1))
/* Checks for 2 ranges overlap */
#define OVERLAP(a0, a1, b0, b1) (LESS(a0, a1, b0, b1) && LESS(b0, b1, a0, a1))
/* Checks for 2 boxes overlap */
#define BOVERLAP(a0, b0, a1, b1, a2, b2, a3, b3) (OVERLAP(a0, a1, a2, a3))

typedef struct s_vec2
{
	float	x;
	float	y;
}				t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct s_sector
{
	float	floor;
	float	ceiling;
	int		num_of_vertecies;
	t_vec2	*vertecies;
	char	*neighbors;
};

typedef struct s_player
{
	t_vec3	position;
	t_vec3	velocity;
	float	angle;
	float	angle_sin;
	float	angle_cos;
	float	yaw;
	int		sector;
}				t_player;
