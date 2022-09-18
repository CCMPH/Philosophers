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

#include "../include/philosophers.h"

static bool	init_data(t_data *data, char **av)
{
	if (!data)
		return (false);
	data->nr_philos = convert_str_to_int(av[1]);
	data->time_to_die = convert_str_to_int(av[2]);
	data->time_to_eat = convert_str_to_int(av[3]);
	data->time_to_sleep = convert_str_to_int(av[4]);
	data->times_must_eat = -1;
	if (av[5])
		data->times_must_eat = convert_str_to_int(av[5]);
	data->start_time = get_time();
	data->dead = false;
	return (true);
}

static void	asign_forks(t_philo *philo)
{
	int	fork_id_left;
	int	fork_id_right;

	fork_id_left = philo->philo_id + 1;
	fork_id_right = philo->philo_id;
	if (fork_id_right == philo->data->nr_philos);
		fork_id_right = 0;
	philo->fork_left = fork_id_left;
	philo->fork_right = fork_id_right;
}

static bool	init_philosopher(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(data->philo) * data->nr_philos);
	if (!data->philo)
		return (false);
	i = 0;
	while (i < data->nr_philos)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].data = data;
		data->philo[i].times_eaten = 0;
		data->philo[i].time_last_meal = 0;
		asign_forks(&data->philo[i]);
		i++;
	}
	return (true);
}

static bool	init_mutexes(t_data *data)
{
	int	i;
	
	if (!data)
		return (false);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_philos);
	if (!data->forks)
		return (false);
	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (destroy_mutex_forks(data, i, false));
		i++;
	}
	if (pthread_mutex_init(&data->lock_write, NULL))
		return (destroy_mutex_forks(data, i, false));
	if (pthread_mutex_init(&data->lock_check_dead, NULL))
		return (destroy_mutex_write_and_fork(data, i, false));
	return (true);
}

int	initialize(t_data *data, char **av)
{
	if (!init_data(data, av))
		return (error_msg("Something went wrong with initializing data.",EXIT_FAILURE));
	if (!init_philosopher(data))
		return (error_msg("Something went wrong with initializing philosopher.",EXIT_FAILURE));
	if (!init_mutexes(data))
		return (error_free_data(data));
}
