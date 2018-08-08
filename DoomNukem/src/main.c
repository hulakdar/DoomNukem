#include "dn_threads.h"
#include "dn_events.h"
#include "dn.h"

int main(void)
{
	t_game_state game_state;

	init_game_state(&game_state);
	start_thread((ROUTINE)game_loop, &game_state);
	start_thread((ROUTINE)draw_loop, &game_state);
	event_handler(&game_state);
}