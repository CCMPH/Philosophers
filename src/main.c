/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:05:08 by chartema      #+#    #+#                 */
/*   Updated: 2022/10/04 16:41:24 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers.h"
#include "../include/philosophers.h"

// void	check_leaks(void)
// {
// 	system("leaks -q a.out");
// }
//atexit(check_leaks);

int	main(int ac, char **av)
{
	t_data	data;

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
