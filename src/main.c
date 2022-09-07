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

#include "philosophers.h"
#include <stdlib.h> //nodig voor exit_failure
#include <stdio.h> //nodig voor printf

// void	philo_think(t_philo *philo)
// {
// 	//dit nog uitwerken met hoe lang moet iemand denken. 
// 	//verschillende senarios uitdenken. 
// }

// void	*simulation(void *data)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)data;
// 	if (philo->data->nr_of_philos == 1)
// 	{
// 		//functie voor als input 1 is
// 		return(0);
// 	}
// 	//even philos beginnen met denken
// 	else if (philo->id_philo % 2)
// 		philo_think(philo);
// }

// int create_threads(t_data *data, t_philo *philo)
// {
// 	int	i;
// 	pthread_t	thread_id[200];

// 	i = 0;
// 	while (i < data->nr_of_philos)
// 	{
// 		if (pthread_create(thread_id, NULL, &simulation, &philo[i]))
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	//nog een tread maken voor een supervisor?
// 	// nog joinen ook
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
		return (error_msg(STR_ERR_INPUT_AMMOUNT, NULL, EXIT_FAILURE));
	if (!is_input_valid(ac, av))
		return (EXIT_FAILURE);
	if (initialize(&data, philo, av))
		return (EXIT_FAILURE);
	// if (create_threads(&data, philo))
	// 	return (EXIT_FAILURE);
	//start_simulation
	//stop_simulation
	printf("succes\n");
	return (0);
}
