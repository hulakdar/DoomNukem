#include "dn_simple_drawing.h"
#include "dn.h"

t_color make_color_from_int(int hex)
{
	return ((t_color){ hex >> 16, hex >> 8, hex });
}

bool depth_test(t_render_state * renderable, int x, int y, float depth)
{
	float *depth_buffer = renderable->depth_buffer;
	depth_buffer += y * renderable->w + x;
	if (*depth_buffer < depth)
		return false;
	*depth_buffer = depth;
	return true;
}

void set_color(t_vec2i point, t_color color);

bool gDebug = true;

void put_pixel(int x, int y, float depth, t_color color)
{
	t_color			*pixels;

	if (depth_test(get_render_state(), x, y, depth))
	{
		depth = max(depth / 50, 1.5);
		color.r /= depth;
		color.g /= depth;
		color.b /= depth;
		set_color((t_vec2i) { x, y }, color);
	}
	else if (gDebug)
		__debugbreak();
}

void draw_vline(t_simple_vline line)
{
	int						y;
	t_render_state	*renderable;

	renderable = get_render_state();
	line.y1 = CLAMP(line.y1, 0, renderable->h);
	line.y2 = CLAMP(line.y2, 0, renderable->h);
	if (line.y2 < line.y1)
		return;
	y = line.y1;
	while (++y < line.y2)
		put_pixel(line.x, y, line.depth, line.color);
}

void del_func(void *ptr, size_t size)
{
	free(ptr);
}

void ft_swapf(float *a, float *b)
{
	float tmp = *a;

	*a = *b;
	*b = tmp;
}

void set_color(t_vec2i point, t_color color)
{
	t_render_state *render_state = get_render_state();
	
	if (point.x < 0 || point.y < 0 || point.x >= render_state->w || point.y >= render_state->h)
		return;

	t_color *pixels = render_state->pixels;
	pixels[point.y * render_state->w + point.x] = color;
}

void brezenheim(t_line line, t_color color)
{
	bool steep = false;
	if (fabs(line.a.x - line.b.x) < fabs(line.a.y - line.b.y))
	{
		ft_swapf(&line.a.x, &line.a.y);
		ft_swapf(&line.b.x, &line.b.y);
		steep = true;
	}
	if (line.a.x > line.b.x) {
		ft_swapf(&line.a.x, &line.b.x);
		ft_swapf(&line.a.y, &line.b.y);
	}
	float dx = line.b.x - line.a.x;
	float dy = line.b.y - line.a.y;
	float derror = fabsf(dy / dx);
	float error = 0;
	int y = line.a.y;
	for (int x = line.a.x; x <= line.b.x; x++)
	{
		if (steep) {
			set_color((t_vec2i){y, x}, color);
		}
		else {
			set_color((t_vec2i){x, y}, color);
		}
		error += derror;
		if (error > .5f) {
			y += (line.b.y > line.a.y ? 1 : -1);
			error -= 1.;
		}
	}
}

void process_sector(t_list **pending_sectors, t_player player)
{
	const t_color colors[] = {COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_YELLOW, COLOR_MAGENTA};
	t_game_state	*game_state = get_game_state();
	t_map			map = *game_state->current_map;
	t_render_state	*render_state = get_render_state();

	short secnum = *(short*)(*pending_sectors)->content;
	t_sector current_sector = map.sectors[secnum];
	t_vec2 *sector_verts = &map.verts[current_sector.start];

	const t_vec2 player_pos = { player.position.x, player.position.y };
	const float pcos = cosf(player.angle);
	const float psin = sinf(player.angle);

	const t_vec2 up = {0, -20000};

	const t_vec2 left_v = rotate_vec2(cosf(-HFOV / 2), sinf(-HFOV / 2), up);
	const t_vec2 right_v = rotate_vec2(cosf(HFOV / 2), sinf(HFOV / 2), up);
	const t_line left_frust = { {0,0}, left_v };
	const t_line right_frust = { {0,0}, right_v };

	for (int i = 0; i < current_sector.length; ++i)
	{
		t_line line = { sector_verts[i], sector_verts[i + 1] };

		// translating everything to player space
		line.a = VEC2_SUB(line.a, player_pos);
		line.b = VEC2_SUB(line.b, player_pos);

		// rotating to player space
		line.a = rotate_vec2(pcos, psin, line.a);
		line.b = rotate_vec2(pcos, psin, line.b);

		const char a_left = determine_side(line.a, left_frust);
		const char b_left = determine_side(line.b, left_frust);
		const char a_right = determine_side(line.a, right_frust);
		const char b_right = determine_side(line.b, right_frust);

		// filtering out walls that we don't face
		if ((a_left < 0 && b_left < 0)
		|| (a_right > 0 && b_right > 0)
		|| (line.a.y >= 0 && line.b.y >= 0))
			continue;

		// frustrum clipping
		if (a_right > 0)
			line.a = line_intersection(line, right_frust);
		if (b_left < 0)
			line.b = line_intersection(line, left_frust);

		// perspective projection

		int x1 = render_state->w / 2 - 1 + (line.b.x / line.b.y) * -render_state->w;
		int x2 = render_state->w / 2 - 1 + (line.a.x / line.a.y) * -render_state->w;

		x1 = CLAMP(x1, 0, render_state->w - 1);
		x2 = CLAMP(x2, 0, render_state->w - 1);

		for (int x = x1; x < x2; x++)
		{
			const int length = x2 - x1;
			float alpha = (x - x1) / (float)length;
			float delimiter = -line.a.y * alpha + -line.b.y * (1 - alpha);
			delimiter = fabs(delimiter);
			int height = render_state->h / delimiter;
			height = CLAMP(height, 0, render_state->h - 1);
			int y1 = render_state->h / 2 - 1 - height / 2;
			int y2 = render_state->h / 2 - 1 + height / 2;
			draw_vline((t_simple_vline) {x, 0, y1, COLOR_ANOTHER, delimiter});
			draw_vline((t_simple_vline) {x, y1, y2, colors[i%ARRAY_COUNT(colors)], delimiter});
			draw_vline((t_simple_vline) {x, y2, render_state->h, COLOR_WHITE, delimiter});
		}
	}
	ft_lstdelone(pending_sectors, del_func);
}

void draw_screen_simple(void)
{
	t_game_state	*game_state = get_game_state();
	t_render_state	*render_state = get_render_state();
	t_list			*pending_sectors;
	const t_player	player = game_state->player;

	int i = 0;
	short k = 1;

	// here we generate bunches
	pending_sectors = ft_lstnew(&game_state->player.sector, sizeof(short));
	pending_sectors->next = ft_lstnew(&k, sizeof(short));
	while (pending_sectors)
		process_sector(&pending_sectors, player);
}
