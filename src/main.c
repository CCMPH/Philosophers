/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:05:08 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/07 14:27:22 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers.h"
#include "../include/philosophers.h"

void	check_leaks(void)
{
	system("leaks -q a.out");
}

static bool	init_data(t_data *data, char **av)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->lock_write);
	// iets maken wanneer simulatie is gestopt zodat niet blijft doorschrijven.
	time = get_time();
	printf("%ld %d %s\n", time - philo->data->start_time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->lock_write);
}

bool	check_dead(t_data *data)
{
	pthread_mutex_lock(&(data->lock_check_dead));
	if (data->dead == true)
	{
		pthread_mutex_unlock(&(data->lock_check_dead));
		return (true);
	}
	pthread_mutex_unlock(&(data->lock_check_dead));
	return (false);
}

void	time_action(unsigned long time_action)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < time_action)
		usleep(10);
}

bool	pick_up_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (left_fork == right_fork)
		return (false);
	pthread_mutex_lock(&(philo->data->forks[right_fork]));
	if (check_dead(philo->data) == true)
	{
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		return (false);
	}
	philo_print(philo, "Picking up fork\n");
	pthread_mutex_lock(&(philo->data->forks[left_fork]));
	if (check_dead(philo->data) == true)
	{
		pthread_mutex_unlock(&(philo->data->forks[left_fork]));
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		return (false);
	}
	philo_print(philo, "Picking up fork\n");
	return (true);
}

void	philo_eat(t_philo *philo)
{
	if (pick_up_forks(philo, philo->fork_left, philo->fork_right) == false)
		return ;
	pthread_mutex_lock(&(philo->lock_eating));
	philo_print(philo, "Eating");
	philo->times_eaten++;
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&(philo->lock_eating));
	time_action(philo->data->time_to_eat);
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_right]));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_left]));
}

bool	check_done(t_data *data, t_philo *philo)
{
	if (philo->times_eaten > 0 && philo->times_eaten == data->times_must_eat)
	{
		data->philos_done_eating++;
		//moet hier een lock op? Wel een data waar iedereen bij kan?
		philo->done_eating = true;
		return (true);
	}
	return (false);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	time_action(philo->data->time_to_sleep);
}

void *philosopher(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if (philo->philo_id % 2)
		usleep(500);
	// usleep 500 - kijken of hier iets anders voor verzonnen moet worden. 
	while (philo->data->dead != true && philo->times_eaten != philo->data->times_must_eat))
	{
		philo_print(philo, "is thinking");
		if (check_dead(philo->data) == true)
			break ;
		philo_eat(philo);
		if (check_dead(philo->data) == true)
			break ;
		if (check_done(philo->data, philo) == true)
			break;
		philo_sleep(philo);
	}
	return (0);
}

bool	create_philo_pthread(t_data *data)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * data->nr_philos);
	if (!threads)
		return (false);
	while (i < data->nr_philos)
	{
		if (pthread_create(&threads[i], NULL, philosopher, &data->philo[i]))
		return (false);
		i++;
	}
	return (true);
}

int	start_simulation(t_data *data)
{
	if (!create_philo_pthread(data))
		return(EXIT_FAILURE);
		//return(error_free_all()) ook free treads vanaf hier //nog naar kijken
	
	// HIER VERDERRR
	//create monitoring
	// join
	
}

int main(int ac, char **av)
{
	t_data	data;

	//atexit(check_leaks);
	if (ac < 5 || ac > 6)
		return (error_msg("Wrong amount of arguments", EXIT_FAILURE));
	if (!is_input_valid(ac, av))
		return (EXIT_FAILURE);
	if (initialize(&data, av))
		return (EXIT_FAILURE);
	if (start_simulation(&data))
		return (EXIT_FAILURE);
	//stop_simulation
	printf("succes\n");
}

// to do:
//
// -*- op school kijken naar headerfiles 
