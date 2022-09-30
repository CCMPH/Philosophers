/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:05:08 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/29 15:25:53 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers.h"
#include "../include/philosophers.h"

void	check_leaks(void)
{
	system("leaks -q a.out");
}

void	philo_print(t_philo *philo, char *str)
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
	//Ik gebruik hier lock_dead, die ik gebruik ik ook in monitor. Kan dit?
	pthread_mutex_lock(&(data->lock_dead));
	if (data->dead == true)
	{
		pthread_mutex_unlock(&(data->lock_dead));
		return (true);
	}
	pthread_mutex_unlock(&(data->lock_dead));
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
	if (philo->philo_id == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		philo_print(philo, "Picking up fork\n");
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		philo_print(philo, "Picking up fork\n");
		return (true);
	}
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
	philo->time_last_meal = get_time();
	time_action(philo->data->time_to_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&(philo->lock_eating));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_right]));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_left]));
}

bool	check_done(t_data *data, t_philo *philo)
{
	//times_eaten moet een lock omheen.
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
		usleep(200);
	// usleep 500 - kijken of hier iets anders voor verzonnen moet worden. 
	while (1)
	{
		philo_print(philo, "is thinking");
		if (check_dead(philo->data) == true)
			break ;
		philo_eat(philo);
		if (check_dead(philo->data) == true)
			break ;
		//if (check_done(philo->data, philo) == true)
		//	break ;
		philo_sleep(philo);
	}
	return (0);
}

bool	create_philo_pthread(t_data *data)
{
	int			i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->nr_philos);
	if (!data->threads)
		return (false);
	while (i < data->nr_philos)
	{
		if (pthread_create(&data->threads[i], NULL, philosopher, &data->philo[i]))
			return (false);
		// errormanagement, check in functie philosopher of alles is gelukt
		i++;
	}
	return (true);
}

void	monitoring(t_data *data)
{
	int		i;
	long	time;

	i = 0;
	while (i < data->nr_philos)
	{
		time = get_time();
		if (time - data->philo[i].time_last_meal >= data->time_to_die)
		{
			pthread_mutex_lock(&data->lock_dead);
			data->dead = true;
			philo_print(data->philo, "died");
			pthread_mutex_unlock(&data->lock_dead);
			break ;
		}
		i++;
		if (i == data->nr_philos)
			i = 0;
	}
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

int	start_simulation(t_data *data)
{
	if (!create_philo_pthread(data))
		return(EXIT_FAILURE);
	//return(error_free_all()) ook free treads vanaf hier //nog naar kijken
	monitoring(data);
	join_threads(data);
	//cleanup
	return (0);
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
// -*- iets voor 1 philo
// -*- errormanagement
// -*- cleanup
