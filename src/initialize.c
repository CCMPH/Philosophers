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

int	init_philosophers(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		philo[i].id_philo = i + 1;
		philo[i].times_eaten = 0;
		philo[i].last_eaten = get_time();
		philo[i].data = data;
		philo[i].left_fork = data->forks[i];
		philo[i].right_fork = data->forks[(i + 1) % data->nr_of_philos];
		// kijken of vorken anders verdeeld moeten worden - asign forks
		if (pthread_create(&data->threads[i], NULL, &simulation, (void *)&philo[i]))
			return (EXIT_FAILURE);
		//is cast naar void nodig?
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;	
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
	data->status = ALIVE;
	return (EXIT_SUCCESS);
}

int	initialize(t_data *data, char **av)
{
	if (init_data(av, data))
		return (EXIT_FAILURE);
	if (init_mutexes(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
