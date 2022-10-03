/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:17:02 by chartema      #+#    #+#                 */
/*   Updated: 2022/10/03 14:19:27 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (data->threads)
		free(data->threads);
}

void	destroy_mutex_philo(t_data *data, int index)
{
	int	i;

	i = index;
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&data->philo[i].lock_eating);
	}
}

void	destroy_mutex_forks(t_data *data, int index)
{
	int	i;

	i = index;
	destroy_mutex_philo(data, data->nr_philos);
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&data->forks[i]);
	}
}

void	destroy_mutex_write_and_fork(t_data *data, int index)
{
	destroy_mutex_forks(data, index);
	pthread_mutex_destroy(&data->lock_write);
}

void	destroy_mutex_all(t_data *data, int index)
{
	destroy_mutex_write_and_fork(data, index);
	pthread_mutex_destroy(&data->lock_dead);
}
