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

int	init_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_of_philos);
	if (!data->forks)
		return (error_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE));
	while (i < data->nr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			//functie die de boel delete mutex_destroy
			//kijken naar de error message
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->lock_philo_dead, NULL))
	{
		//functie die de boel delete mutex_destroy
		//kijken naar de error message
		return (1);
	}
	if (pthread_mutex_init(&data->lock_write, NULL))
	{
		//functie die de boel delete mutex_destroy
		//kijken naar de error message
		return (1);
	}
	return (0);
}

int init_data(char **av, t_data *data)
{
	data->nr_of_philos = convert_str_to_int(av[1]);
	data->time_to_die = convert_str_to_int(av[2]);
	data->time_to_eat = convert_str_to_int(av[3]);
	data->time_to_sleep = convert_str_to_int(av[4]);
	data->times_must_eat = -1;
	if (av[5])
		data->times_must_eat = convert_str_to_int(av[5]);
	data->start_time = get_time();
	//data->done_eating = 0;
	//data->dead = false';
	if (init_mutex(data))
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (error_msg(STR_ERR_INPUT_AMMOUNT, NULL, EXIT_FAILURE));
	if(!is_input_valid(ac, av))
		return (EXIT_FAILURE);
	if (init_data(av, &data))
		return (EXIT_FAILURE);
	//start_simulation
	//stop_simulation
	printf("succes\n");
	return (0);
}

// to do:
// initialize functie verder maken