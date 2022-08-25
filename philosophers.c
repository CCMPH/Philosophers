/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:05:08 by chartema      #+#    #+#                 */
/*   Updated: 2022/08/23 10:05:19 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	*data;
	//t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (error_msg("Wrong amount of arguments"));
	//if (initialize_args(ac, av, &data, &philo));
	if (initialize_args(ac, av, &data));
		return (1);
	return (0);
}

// to do:
// errormsg aanpassen naar so_long variant
// initialize functie verder maken + checks