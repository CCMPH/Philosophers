#include "philosophers.h"

#include <stddef.h> //nodig voor NULL
#include <limits.h> //nodig voor int_MAX

static bool is_input_a_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	convert_str_to_int(char *str)
{
	unsigned long	nb;
	int				i;
	
	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

bool	is_input_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if(!is_input_a_digit(av[i]))
			return (error_msg(STR_ERR_INPUT_DIGIT, av[i], false));
		nb = convert_str_to_int(av[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
			return (error_msg(STR_ERR_PHILO, NULL, false));
		if (i != 1 && nb == 0)
			return (error_msg(STR_ERR_ARG_ZERO, NULL, false));
		if (i != 1 && nb == -1)
			return (error_msg(STR_ERR_MAX_INT, NULL, false));
		i++;
	}
	return (true);
}