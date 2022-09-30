/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:18:49 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/30 11:05:08 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	convert_str_to_int(char *str)
{
	unsigned long	nb;
	int				i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//kijken naar de printfunctie!

void	philo_print(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->lock_write);
	if (check_dead(philo->data) == false)
	{
		time = get_time();
		printf("%ld %d %s\n", time - philo->data->start_time, philo->philo_id, str);
	}
	pthread_mutex_unlock(&philo->data->lock_write);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}
