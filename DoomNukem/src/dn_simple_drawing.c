#include "dn_simple_drawing.h"
#include "dn.h"

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
	renderable->pixels[line.y2 * renderable->w + line.x] = 0xFF0000;
}

void draw_screen_simple(t_game_state *game_state)
{
	t_item	items[32];
	t_item	*head = items;
	t_item	*tail = items;

	int *ytop = ft_memalloc(game_state->render_state.w);
	int *ybottom = ft_memalloc(game_state->render_state.w);
	int	rendersectors[512] = { 0 };
	ft_memset(ybottom, game_state->render_state.h - 1, game_state->render_state.w);

	




	free(ytop);
}
