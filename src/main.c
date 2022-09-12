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
#include "../include/philosophers.h"
#include <stdlib.h> //nodig voor exit_failure
#include <stdio.h> //nodig voor printf
#include <unistd.h> //nodig voor usleep

// ipv 500 laten slapen, functie uitbreiden zodat hij preciezer is
// void	philo_think(t_philo *philo)
// {
// 	//dit nog uitwerken met hoe lang moet iemand denken. 
// 	//verschillende senarios uitdenken. 
// }

void	philo_print()
{

}

bool	check_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (left_fork == right_fork)
		return (false);
	phtread_mutex_lock(&philo->data->forks[right_fork]);
	// check of is dood??
	philo_print();
	// VERDER MET PHILO PRINT EN DE SIMULATION
}


void	philo_eat(t_philo *philo)
{
	if (check_forks(philo, philo->left_fork, philo->right_fork))
		return ;
	
}


void	*simulation(void *philosopher)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	if (philo->id_philo % 2)
		usleep(500);
	//printf("Philo id: %d\n", philo->id_philo);
	while (data->status != DEAD && philo->times_eaten != data->times_must_eat)
	{
		//philo_print
		philo_eat(philo);
	}
	return (0);
}

int	join_threads(t_data *data)
{
	unsigned i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		pthread_join(data->threads[i], NULL);
		//error management toepassen hiero
		i++;
	}
	return (EXIT_SUCCESS);
}


int start_simulation(t_data *data)
{
	t_philo		*philo;

	philo = malloc(sizeof(*philo) * data->nr_of_philos);
	if (!philo)
		return (error_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE));
	init_philosophers(data, philo);
	join_threads(data);
	//nog een tread maken voor een supervisor?
	// boel opschonen
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (error_msg(STR_ERR_INPUT_AMMOUNT, NULL, EXIT_FAILURE));
	if (!is_input_valid(ac, av))
		return (EXIT_FAILURE);
	if (initialize(&data, av))
		return (EXIT_FAILURE);
	if (start_simulation(&data))
		return (EXIT_FAILURE);
	//stop_simulation
	printf("succes\n");
	return (0);
}
