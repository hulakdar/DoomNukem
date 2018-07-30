#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include "dn_math.h"

#include <SDL.h>
#undef main

/* Numbers are arbitrary */
#define W 608
#define H 480

#define EYE_HEIGHT 6.f
#define DUCK_HEIGHT 2.5f
#define HEAD_MARGIN 1.f
#define KNEE_HEIGHT 2.f
#define HFOV (0.73f * H)
#define VFOV (.2f * H)

/* Checks for 2 boxes overlap */
#define BOVERLAP(a0, b0, a1, b1, a2, b2, a3, b3) (OVERLAP(a0, a1, a2, a3))


typedef struct s_sector
{
	float		floor;
	float		ceil;
	unsigned	npoints;
	t_vec2		*vertex;
	char		*neighbors;
}				t_sector;

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
