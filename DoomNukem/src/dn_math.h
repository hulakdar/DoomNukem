#pragma once
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

/*
** Helper macros
*/
#define VEC2(type) struct s_vec2##type{type x;type y;}
#define VEC3(type) struct s_vec3##type{type x;type y;type z;}
#define VEC4(type) struct s_vec4##type{type x;type y;type z; type w;}

/*
** "Templated" structs
*/
#define DECL_VEC2(type, name) typedef VEC2(type) name;
#define DECL_VEC3(type, name) typedef VEC3(type) name;
#define DECL_VEC4(type, name) typedef VEC4(type) name;

/*
** If you need another vector type (2d or 3d), just add another macro here
** Cool, right?
*/
DECL_VEC2(int, t_vec2i)
DECL_VEC2(short, t_vec2s)
DECL_VEC2(float, t_vec2)
DECL_VEC3(float, t_vec3)
DECL_VEC3(char, t_vec3c)

typedef struct s_line
{
	t_vec2	a;
	t_vec2	b;
}				t_line;

typedef t_line t_box;

/*
** Everything here is stolen from Bisqwit
*/

/* Math "templated" macro */
#define CLAMP(a, mi, ma)  min(max(a, mi), ma)
/* Helper macro. Hate norm */
#define LESS(a0, a1, b0, b1) (min(a0, a1) <= max(b0, b1))
/* Checks for 2 ranges overlap */
#define OVERLAP(a0, a1, b0, b1) (LESS(a0, a1, b0, b1) && LESS(b0, b1, a0, a1))

/*
** Vector cross product in 2D. Returns a float. this is not a mistake.
*/
#define CROSS(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))

/*
** Check whether 2 boxes intersect. Doesn't work with lines.
*/
bool	boxes_intersect(t_box a, t_box b);

/*
** Figure out on which side of the line the point is
*/
char	determine_side(t_vec2 point, t_line line);

/*
** Find the point where 2 lines intersect
*/
t_vec2	line_intersection(t_line a, t_line b);