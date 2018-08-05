#include "dn_events.h"
#include "dn.h"

void event_handler(t_game_state *game_state)
{
	SDL_Event e;

	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return;
		}
	}
}
