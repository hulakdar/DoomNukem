#include "dn_math.h"

bool boxes_intersect(t_box first, t_box second)
{
	return (OVERLAP(first.a.x, first.b.x, second.a.x, second.b.x)
		&& OVERLAP(first.a.y, first.b.y, second.a.y, second.b.y));
}

char determine_side(t_vec2 point, t_line line)
{
	const float result = CROSS(line.b.x - line.a.x, line.b.y - line.a.y,
		point.x - line.a.x, point.y - line.a.y);

	if (result == 0.f)
		return (0);
	else if (result > 0)
		return 1;
	return -1;
}

t_vec2 line_intersection(t_line one, t_line two)
{
	const t_vec2 cross = {
		CROSS(one.a.x, one.a.y, one.b.x, one.b.y),
		CROSS(two.a.x, two.a.y, two.b.x, two.b.y)
	};
	const t_vec2 sub_one = {
		one.a.x - one.b.x,
		one.a.y - one.b.y
	};
	const t_vec2 sub_two = {
		two.a.x - two.b.x,
		two.a.y - two.b.y
	};
	const float delimiter = CROSS(sub_one.x, sub_one.y, sub_two.x, sub_two.y);
	return ((t_vec2) {
		CROSS(cross.x, sub_one.x, cross.y, sub_two.x) / delimiter,
		CROSS(cross.x, sub_one.y, cross.y, sub_two.y) / delimiter
	});
}
