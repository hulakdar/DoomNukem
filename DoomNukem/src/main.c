#include "dn.h"

int main(void)
{
	t_render_state render_state;
	render_state.w = 640;
	render_state.h = 480;

	if (init_render_state(&render_state))
		return(-1);

	SDL_Event e;
	while (true)
	{
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT)
				return (0);
		SDL_RenderPresent(render_state.renderer);
	}
}