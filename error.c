#include "philosophers.h"

#include <stdio.h> //nodig voor printf

int	error_msg(char *str, char *extra_msg, int exit_nr)
{
	if (!extra_msg)
		printf(str, STR_ERROR);
	else
		printf(str, STR_ERROR ,extra_msg);
	return (exit_nr);
}