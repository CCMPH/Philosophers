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

void *philosopher(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if (philo->philo_id % 2)
		usleep(500);
	
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
