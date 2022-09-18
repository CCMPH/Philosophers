/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:17:02 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/07 10:17:15 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_msg(char *str, int status)
{
	printf("%s\n", str);
	return(status);
}

int	error_free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	return(error_msg("Something went wrong with initializing mutexes.", EXIT_FAILURE));
}

bool	destroy_mutex_forks(t_data *data, int index, bool info)
{
	int	i;

	i = index;
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&data->forks[i]);
	}
	return (info);
}

bool	destroy_mutex_write_and_fork(t_data *data, int index, bool info)
{
	pthread_mutex_destroy(&data->lock_write);
	destroy_mutex_forks(data, index, info);
	return (info);
}
