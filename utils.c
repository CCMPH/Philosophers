#include "philosophers.h"


int	error_msg(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}