/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 09:28:34 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/30 14:12:43 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers.h"
#include "../include/philosophers.h"

void	time_action(unsigned long time_action, t_data *data)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start <= time_action)
	{
		if (check_dead(data) == true)
			return ;
		usleep(100);
	}
}

bool	pick_up_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->philo_id == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		philo_print(philo, "has taken a fork");
		return (true);
	}
	pthread_mutex_lock(&(philo->data->forks[right_fork]));
	if (check_dead(philo->data) == true)
	{
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		return (false);
	}
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->data->forks[left_fork]));
	if (check_dead(philo->data) == true)
	{
		pthread_mutex_unlock(&(philo->data->forks[left_fork]));
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		return (false);
	}
	philo_print(philo, "has taken a fork");
	return (true);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	time_action(philo->data->time_to_sleep, philo->data);
}

void	philo_eat(t_philo *philo)
{
	if (pick_up_forks(philo, philo->fork_left, philo->fork_right) == false)
		return ;
	pthread_mutex_lock(&(philo->lock_eating));
	philo_print(philo, "is eating");
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&(philo->lock_eating));
	time_action(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&(philo->lock_eating));
	philo->times_eaten++;
	pthread_mutex_unlock(&(philo->lock_eating));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_right]));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_left]));
}
