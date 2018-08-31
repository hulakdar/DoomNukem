#pragma once

#if defined(__WIN32__) || defined (_WIN32) || defined (WIN32)
long	Sleep(unsigned long ms);
#define WAIT(x) (Sleep(x))
#else
#define WAIT(x) (sleep(x))
#endif

void	event_handler(void);
int		create_window(int width, int height);