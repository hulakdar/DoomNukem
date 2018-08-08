#include "dn_threads.h"

pthread_t start_thread(void *(*function)(void *), void *user_data)
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, function, user_data);
	return thread_id;
}
