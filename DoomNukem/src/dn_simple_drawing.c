#include "dn_simple_drawing.h"
#include "dn.h"

t_color make_color_from_int(int hex)
{
	return ((t_color){ hex >> 16, hex >> 8, hex });
}

void draw_vline(t_render_state *renderable, t_simple_vline line)
{
	t_color					*pixels;
	int						y;

	pixels = renderable->pixels;
	line.y1 = CLAMP(line.y1, 0, renderable->h);
	line.y2 = CLAMP(line.y2, 0, renderable->h);
	if (line.y2 < line.y1)
		return;
	y = line.y1;
	pixels[(y * renderable->w) + line.x] = COLOR_GREEN;
	while (++y < line.y2)
		pixels[(y * renderable->w) + line.x] = line.color;
	pixels[(y * renderable->w) + line.x] = COLOR_GREEN;
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

void brezenheim(t_line line, t_color color) {
	bool steep = false;
	if (fabs(line.a.x - line.b.x) < fabs(line.a.y - line.b.y)) {
		ft_swapf(&line.a.x, &line.a.y);
		ft_swapf(&line.b.x, &line.b.y);
		steep = true;
	}
	if (line.a.x > line.b.x) {
		ft_swapf(&line.a.x, &line.b.x);
		ft_swapf(&line.a.y, &line.b.y);
	}
	double dx = line.b.x - line.a.x;
	double dy = line.b.y - line.a.y;
	double derror = fabs(dy / dx);
	double error = 0;
	int y = line.a.y;
	for (int x = line.a.x; x <= line.b.x; x++) {
		if (steep) {
			set_color((t_vec2i){y, x}, color);
		}
		else {
			set_color((t_vec2i){x, y}, color);
		}
		error += derror;
		if (error > .5) {
			y += (line.b.y > line.a.y ? 1 : -1);
			error -= 1.;
		}
	}
}

void process_sector(t_list **pending_sectors)
{
	const t_color colors[] = {COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_WHITE};
	t_game_state	*game_state = get_game_state();
	t_map			map = *game_state->current_map;
	//t_render_state	*render_state = get_render_state();

	short secnum = *(short*)(*pending_sectors)->content;
	t_sector current_sector = map.sectors[secnum];
	t_vec2 *sector_verts = &map.verts[current_sector.start];

	const t_player player = game_state->player;
	const t_vec2 player_pos = { player.position.x, player.position.y };
	const float pcos = cosf(player.angle);
	const float psin = sinf(player.angle);

	const t_vec2 up = {0, -20};

	const t_vec2 left_v = rotate_vec2(cosf(-HFOV / 2), sinf(-HFOV / 2), up);
	const t_vec2 right_v = rotate_vec2(cosf(HFOV / 2), sinf(HFOV / 2), up);
	const t_line left_frust = { {0,0}, left_v };
	const t_line right_frust = { {0,0}, right_v };

	for (int i = 0; i < current_sector.length; ++i)
	{
		const t_line line = { sector_verts[i], sector_verts[i + 1] };

		// translating everything to player space
		t_vec2 v1 = VEC2_SUB(line.a, player_pos);
		t_vec2 v2 = VEC2_SUB(line.b, player_pos);

		// rotating to player space
		v1 = rotate_vec2(pcos, psin, v1);
		v2 = rotate_vec2(pcos, psin, v2);

		// filter out walls that we don't face
		const bool a_left = determine_side(v1, left_frust) >= 0;
		const bool b_left = determine_side(v2, left_frust) >= 0;
		const bool a_right = determine_side(v2, right_frust) <= 0;
		const bool b_right = determine_side(v2, right_frust) <= 0;

//TODO: do frustrum clipping to avoid edges from behind leaking into view

		// DEBUG MINI-MAP
		{
			t_line local_line = { v1, v2 };
			local_line.a.x += 400;
			local_line.b.x += 400;
			local_line.a.y += 300;
			local_line.b.y += 300;
			brezenheim(local_line, colors[(a_left && b_left) | ((a_right && b_right) << 1)]);
		}
		// END DEBUG MINI-MAP

		// TODO: transform to screen space and draw
	}
	ft_lstdelone(pending_sectors, del_func);
}

void draw_screen_simple(void)
{
	t_game_state	*game_state = get_game_state();
	t_render_state	*render_state = get_render_state();
	t_list			*pending_sectors;

	int i = 0;
	short k = 1;

	// here we generate bunches
	pending_sectors = ft_lstnew(&game_state->player.sector, sizeof(short));
	pending_sectors->next = ft_lstnew(&k, sizeof(short));
	while (pending_sectors)
		process_sector(&pending_sectors);
	
	const t_vec2 player_pos = { 400, 300 };
	const t_vec2 up = {0, -20};
	const t_vec2 left_frust = rotate_vec2(cosf(-HFOV / 2), sinf(-HFOV / 2), up);
	const t_vec2 right_frust = rotate_vec2(cosf(HFOV / 2), sinf(HFOV / 2), up);
	brezenheim((t_line) { player_pos, VEC2_ADD(player_pos, up) }, COLOR_WHITE);
	brezenheim((t_line) { player_pos, VEC2_ADD(player_pos, left_frust) }, COLOR_GREEN);
	brezenheim((t_line) { player_pos, VEC2_ADD(player_pos, right_frust) }, COLOR_GREEN);
}
