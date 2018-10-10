#include "dn_simple_drawing.h"
#include "dn.h"

t_vec2	walls[] = {
	{0, 0},
	{0, 20},
	{20, 20},
	{20, 0},
	{0, 0},
	{0, 20},
	{0, 40},
	{20, 40},
	{20, 20},
	{0, 20}
};

t_sector sectors[] =
{
	{0, 10, 0, 4},
	{0, 10, 5, 3}
};

short	neighbours[] = {
	-1, 1, -1, -1, -1, -1, 0, -1
};

void draw_vline(t_renderable *renderable, t_simple_vline line)
{
	int						*pixels;
	int						y;

	pixels = renderable->pixels;
	line.y1 = CLAMP(line.y1, 0, renderable->h);
	line.y2 = CLAMP(line.y2, 0, renderable->h);
	if (line.y2 < line.y1)
		return;
	pixels[(line.y1 * renderable->w) + line.x] = 0xFF0000;
	y = line.y1;
	while (y++ < line.y2)
		pixels[(y * renderable->w) + line.x] = line.color;
	renderable->pixels[line.y2 * renderable->w + line.x] = 0xFF00;
}

void draw_screen_simple()
{
	t_item	queue[32];
	t_item	*head = queue;
	t_item	*tail = queue;
	t_game_state *game_state = get_game_state();
	t_render_state render_state = *get_render_state();
	t_player player = game_state->player;

	int renderedsectors[512];

	int *ytop = ft_memalloc(render_state.w);
	int *ybot = malloc(render_state.w);
	ft_memset(ybot, render_state.h - 1, render_state.w);


	
	free(ytop);
	free(ybot);
}
