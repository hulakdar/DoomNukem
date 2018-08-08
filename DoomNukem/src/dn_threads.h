#pragma once

#include <pthread.h>

#define ROUTINE void *(*)(void *)

pthread_t start_thread(void *(*function)(void *), void *user_data);
