/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 10:05:08 by chartema      #+#    #+#                 */
/*   Updated: 2022/08/23 10:05:19 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h> //nodig voor exit_failure
#include <stdio.h> //nodig voor printf

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;	
	while (i < data->nr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			//functie die de boel delete mutex_destroy
			//kijken naar de error message
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->lock_philo_dead, NULL))
	{
		//functie die de boel delete mutex_destroy
		//kijken naar de error message
		return (1);
	}
	if (pthread_mutex_init(&data->lock_write, NULL))
	{
		//functie die de boel delete mutex_destroy
		//kijken naar de error message
		return (1);
	}
	return (0);
}

int	init_philosophers(t_data *data, t_philo *philo)
{
	int	i;

	philo = malloc(sizeof(*philo) * data->nr_of_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_of_philos);
	if (!philo || !data->forks)
		return (error_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE));
	// kijken naar errormsg, ik denk lek als 1e goed gaat, 2e niet
	i = 0;
	while (i < data->nr_of_philos)
	{
		philo[i].id_philo = i + 1;
		philo[i].times_eaten = 0;
		philo[i].last_eaten = get_time();
		philo[i].data = data;
		philo[i].left_fork = data->forks[i];
		philo[i].right_fork = data->forks[(i + 1) % data->nr_of_philos];
		i++;
	}
	return (0);
}

int init_data(char **av, t_data *data)
{
	data->nr_of_philos = convert_str_to_int(av[1]);
	data->time_to_die = convert_str_to_int(av[2]);
	data->time_to_eat = convert_str_to_int(av[3]);
	data->time_to_sleep = convert_str_to_int(av[4]);
	data->times_must_eat = -1;
	if (av[5])
		data->times_must_eat = convert_str_to_int(av[5]);
	else
		data->times_must_eat = 0;
	data->start_time = get_time();
	//data->status = dead or alive;
	return (0);
}

int	initialize(t_data *data, t_philo *philo, char **av)
{
	if (init_data(av, data))
		return (EXIT_FAILURE);
	if (init_philosophers(data, philo))
		return (EXIT_FAILURE);
	if (init_mutexes(data))
		return (EXIT_FAILURE);
}

void	philo_think(t_philo *philo)
{
	//dit nog uitwerken met hoe lang moet iemand denken. 
	//verschillende senarios uitdenken. 
}


void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->nr_of_philos == 1)
	{
		//functie voor als input 1 is
		return(0);
	}
	//even philos beginnen met denken
	else if (philo->id_philo % 2)
		philo_think(philo);
	

}

int create_threads(t_data *data, t_philo *philo)
{
	int	i;
	pthread_t	thread_id[200];
	
	i = 0;
	while (i < data->nr_of_philos)
	{
		if(pthread_create(thread_id, NULL, &simulation, &philo[i]))
			return(EXIT_FAILURE);
		i++;
	}
	//nog een tread maken voor een supervisor?
	// nog joinen ook
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (error_msg(STR_ERR_INPUT_AMMOUNT, NULL, EXIT_FAILURE));
	if(!is_input_valid(ac, av))
		return (EXIT_FAILURE);
	if (initialize(&data, philo, av))
		return(EXIT_FAILURE);
	if (create_threads(&data, philo))
	//start_simulation
	//stop_simulation
	printf("succes\n");
	return (0);
}

// to do:
// initialize functie verder maken