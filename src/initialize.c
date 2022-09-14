/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:34:43 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/07 14:31:49 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "../include/philosophers.h"
#include <stdlib.h> //nodig voor exit_failure
#include <stdio.h> //nodig voor printf

void	mutex_clean(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock_write);
	pthread_mutex_destroy(&data->lock_philo_dead);
}

static int	init_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_of_philos);
	if (!data->forks)
		return (1);
	while (i < data->nr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->lock_write, NULL))
		return (1);
	if (pthread_mutex_init(&data->lock_philo_dead, NULL))
		return (1);
	return (0);
}

static int	init_data(char **av, t_data *data)
{
	data->nr_of_philos = convert_str_to_int(av[1]);
	data->time_to_die = convert_str_to_int(av[2]);
	data->time_to_eat = convert_str_to_int(av[3]);
	data->time_to_sleep = convert_str_to_int(av[4]);
	data->times_must_eat = -1;
	if (av[5])
		data->times_must_eat = convert_str_to_int(av[5]);
	data->start_time = get_time();
	data->dead = false;
	return (EXIT_SUCCESS);
}

int	initialize(t_data *data, char **av)
{
	if (init_data(av, data))
		return (EXIT_FAILURE);
	if (init_mutexes(data))
	{
		if(data->forks)
			free(data->forks);
		mutex_clean(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
