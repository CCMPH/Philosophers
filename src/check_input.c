/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:16:04 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/07 10:25:18 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

bool is_input_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!is_input_a_digit(av[i]))
			return (error_msg("Input contains not only digits.", EXIT_FAILURE));
		nb = convert_str_to_int(av[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
			return (error_msg("There must be between 1 and 200 philosophers.", EXIT_FAILURE));
		if (i != 1 && nb == 0)
			return (error_msg("Arguments can't be zero.", EXIT_FAILURE));
		if (i != 1 && nb == -1)
			return (error_msg("Arguments can't be bigger than MAX_INT.", EXIT_FAILURE));
		i++;
	}
	return (true);
}