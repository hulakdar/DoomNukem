#pragma once

#if defined(__WIN32__) || defined (_WIN32) || defined (WIN32)
#define WAIT(x) (Sleep(x))
#else
#define WAIT(x) (sleep(x))
#endif

void event_handler( struct s_game_state *game_state );