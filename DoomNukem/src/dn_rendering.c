#include "dn_rendering.h"
#include "dn_render_helpers.h"
#include "dn_simple_drawing.h"
#include "dn_events.h"
#include "dn_io.h"
#include "dn.h"
#include "dn_render_helpers.h"

t_render_state * get_render_state(void)
{
	static t_render_state render_state;

	return &render_state;
}

void	draw_loop()
{
	t_render_state *render_state;

	render_state = init_render_state();
	while (1)
	{
		for (int i = 0; i < render_state->h * render_state->w; ++i)
			render_state->pixels[i] = COLOR_BLACK;
		for (int i = 0; i < render_state->h * render_state->w; ++i)
			render_state->depth_buffer[i] = INFINITY;
		draw_screen_simple();
		end_render_frame();
	}
}
