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
	int dx = line.b.x - line.a.x;
	int dy = line.b.y - line.a.y;
	float derror = fabs((float)dy / (float)dx);
	float error = 0;
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
	t_game_state	*game_state = get_game_state();
	t_map			map = *game_state->current_map;
	short secnum = *(short*)(*pending_sectors)->content;
	t_sector current_sector = map.sectors[secnum];
	t_vec2 *sector_verts = &map.verts[current_sector.start];

	for (int i = 0; i < current_sector.length; ++i)
	{
		// TODO: filter out walls that we don't face
		t_line line = { sector_verts[i], sector_verts[i + 1] };
		line.a.x += 10;
		line.b.x += 10;
		line.a.y += 10;
		line.b.y += 10;
		brezenheim(line, COLOR_BLUE);
	}
	ft_lstdelone(pending_sectors, del_func);
}

void draw_screen_simple(void)
{
	t_game_state	*game_state = get_game_state();
	t_render_state	*render_state = get_render_state();
	t_list			*pending_sectors;

	pending_sectors = ft_lstnew(&game_state->player.sector, sizeof(short));
	while (pending_sectors)
	{
		process_sector(&pending_sectors);
		
	}
}
