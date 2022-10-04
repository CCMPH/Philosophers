/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 09:25:56 by chartema      #+#    #+#                 */
/*   Updated: 2022/10/04 16:25:51 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers.h"
#include "../include/philosophers.h"

static void	*philosopher(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if (philo->data->nr_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->philo_id % 2)
		philo_think(philo);
	while (true)
	{
		if (check_dead(philo->data) == true)
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (0);
}

bool	simulation(t_data *data)
{
	int			i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->nr_philos);
	while (i < data->nr_philos && data->threads)
	{
		if (pthread_create(&data->threads[i], NULL, philosopher,
				&data->philo[i]))
			break ;
		i++;
	}
	if (i == data->nr_philos)
		monitoring(data);
	else
	{
		pthread_mutex_lock(&data->lock_dead);
		data->dead = true;
		pthread_mutex_unlock(&data->lock_dead);
	}
	join_threads(data, i);
	destroy_mutex_all(data, data->nr_philos);
	free_data(data);
	return (true);
}
