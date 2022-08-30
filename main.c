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
#include <stdlib.h> //nodig voor exit_failure
#include <stdio.h> //nodig voor printf

t_data *init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (error_null(STR_ERR_MALLOC, NULL));
	data->nr_of_philos = convert_str_to_int(av[1]);
	data->time_to_die = convert_str_to_int(av[2]);
	data->time_to_eat = convert_str_to_int(av[3]);
	data->time_to_sleep = convert_str_to_int(av[4]);
	data->times_must_eat = -1;
	if (ac == 6)
		data->times_must_eat = convert_str_to_int(av[5]);
	// INIT PHILOO MOET HIER NOG BIJ KOMEN
	return (data);
}

int main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		return (error_msg(STR_ERR_INPUT_AMMOUNT, NULL, EXIT_FAILURE));
	if(!is_input_valid(ac, av))
		return (EXIT_FAILURE);
	data = init_data(ac, av);
	if (!data)
		return (EXIT_FAILURE);
	//start_simulation
	//stop_simulation
	printf("succes\n");
	return (0);
}

// to do:
// initialize functie verder maken