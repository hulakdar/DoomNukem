#pragma once

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

typedef struct s_line
{
	t_vec2	a;
	t_vec2	b;
}				t_line;

typedef t_line t_box;

/* Math "templated" macro */
#define CLAMP(a, mi, ma)  min(max(a, mi), ma)

/* Helper macro. Hate norm */
#define LESS(a0, a1, b0, b1) (MIN(a0, a1) <= MAX(b0, b1))
/* Checks for 2 ranges overlap */
#define OVERLAP(a0, a1, b0, b1) (LESS(a0, a1, b0, b1) && LESS(b0, b1, a0, a1))

/* Check whether 2 boxes intersect */
bool	boxes_intersect(t_box a, t_box b);

/* Figure out on which side of the line the point is */
char	determine_side(t_vec2 point, t_line line);

/* Find the point where 2 lines intersect */
t_vec2	line_intersection(t_line a, t_line b);