#include "dn_threads.h"
#include "dn_events.h"
#include "dn.h"

int main(void)
{
	init_game_state();
	create_window(640, 480);
	start_thread((ROUTINE)game_loop, NULL);
	start_thread((ROUTINE)draw_loop, NULL);
	event_handler();
}