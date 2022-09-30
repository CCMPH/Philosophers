/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 09:25:56 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/30 14:25:59 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers.h"
#include "../include/philosophers.h"

static void	*philosopher(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	// if (philo->philo_id % 2)
	// 	usleep(200);
	// usleep 500 - kijken of hier iets anders voor verzonnen moet worden. 
	// functie is thinking. en die dan na sleep nog een keer/.
	while (1)
	{
		// if (check_dead(philo->data) == true)
		// 	break ;
		philo_eat(philo);
		if (check_dead(philo->data) == true)
			break ;
		philo_sleep(philo);
		philo_print(philo, "is thinking");
	}
	return (0);
}

static bool	create_philo_pthread(t_data *data)
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
		// errormanagement, check in functie philosopher of alles is gelukt anders alleen joinen voor wat wel is gelukt. 
		i++;
	}
	return (true);
}

int	start_simulation(t_data *data)
{
	if (!create_philo_pthread(data))
		return(EXIT_FAILURE);
	//return(error_free_all()) ook free treads vanaf hier //nog naar kijken
	// is i niet mijn aantal philoos dan geen monitor, ook op dead = true zetten.
	monitoring(data);
	join_threads(data);
	//cleanup
	return (0);
}
