#include "dn_io.h"
#include "libft.h"

void print_error(const char *message, const char *file, long line)
{
	ft_putstr_fd("Error in file: ", 2);
	ft_putendl_fd(file, 2);
	ft_putstr_fd("On line: ", 2);
	ft_putnbr_fd(line, 2);
	ft_putendl_fd("", 2);
	ft_putendl_fd(message, 2);
	ft_putendl_fd("", 2);
}
