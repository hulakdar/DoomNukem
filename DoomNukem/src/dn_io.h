#pragma once

#define ERROR(x) (print_error(x, __FILE__, __LINE__))

void print_error(const char *message, const char *file, long line);