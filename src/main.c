/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:05:08 by chartema      #+#    #+#                 */
/*   Updated: 2022/10/03 14:16:09 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers.h"
#include "../include/philosophers.h"

void	check_leaks(void)
{
	system("leaks -q a.out");
}

int	main(int ac, char **av)
{
	t_data	data;

	//atexit(check_leaks);
	if (ac < 5 || ac > 6)
		return (printf("%s\n", ERR_ARG), EXIT_FAILURE);
	if (is_input_valid(ac, av) == false)
		return (EXIT_FAILURE);
	if (initialize(&data, av) == false)
		return (EXIT_FAILURE);
	if (simulation(&data) == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// to do:
//
// -*- op school kijken naar headerfiles 
// -*- iets voor 1 philo
// -*- errormanagement
// -*- cleanup
