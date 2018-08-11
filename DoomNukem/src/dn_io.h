#pragma once

#if defined(__WIN32__) || defined (_WIN32) || defined (WIN32)
#define DN_ERROR(x) (print_error(x, __FILE__, __LINE__));__debugbreak()
#else
#define DN_ERROR(x) (print_error(x, __FILE__, __LINE__))
#endif

void print_error(const char *message, const char *file, long line);