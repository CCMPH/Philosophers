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

void	philo_print(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->lock_write);
	// iets maken wanneer simulatie is gestopt zodat niet blijft doorschrijven.
	time = get_time();
	printf("%ld %d %s\n", time - philo->data->start_time, philo->id_philo, str);
	pthread_mutex_unlock(&philo->data->lock_write);
}

void	time_action(unsigned long time_action)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < time_action)
		usleep(10);
}

void	philo_eat(t_philo *philo)
{
	// if (philo->data->dead == true || philo->times_eaten == philo->data->times_must_eat)
	// 	return ; twijfel of dit nodig is
	pthread_mutex_lock(&philo->left_fork);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->lock_meal_time);
	philo_print(philo, "is eating");
	philo->last_eaten = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->lock_meal_time);
	time_action(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	time_action(philo->data->time_to_sleep);
}

void	*simulation(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->id_philo % 2)
		usleep(500);
	while (philo->data->dead != true && philo->times_eaten != philo->data->times_must_eat)
	{
		philo_print(philo, "is thinking");
		philo_eat(philo);
		philo_sleep(philo);
		// wanneer eat max bereikt, gaan we dan nog slapen? zo ja, hier iets extra maken en hoe zit dit met dood gaan?
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
	pthread_join(data->check_stop_sim, NULL);
	return (EXIT_SUCCESS);
}

int	init_philosophers(t_data *data, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->nr_of_philos)
	{
		philo[i].id_philo = i + 1;
		philo[i].times_eaten = 0;
		philo[i].last_eaten = get_time();
		philo[i].data = data;
		philo[i].left_fork = data->forks[i];
		philo[i].right_fork = data->forks[(i + 1) % data->nr_of_philos];
		// kijken of vorken anders verdeeld moeten worden - asign forks
		if (pthread_create(&data->threads[i], NULL, &simulation, (void *)&philo[i]))
			return (EXIT_FAILURE);
		//is cast naar void nodig?
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*supervisor(void *philosopher)
{
	t_philo	*philo;
	unsigned int	i;
	unsigned long	time;

	philo = (t_philo *)philosopher;
	i = 0;
	while (i < philo->data->nr_of_philos)
	{
		time = get_time();
		if (time - philo[i].last_eaten >= philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->lock_philo_dead);
			philo->data->dead = true;
			philo_print(philo, "died");
			pthread_mutex_unlock(&philo->data->lock_philo_dead);
			break;
		}
		i++;
		if (i == philo->data->nr_of_philos)
			i = 0;
	}
	return (0);
}


int start_simulation(t_data *data)
{
	t_philo		*philo;

	philo = malloc(sizeof(*philo) * data->nr_of_philos);
	if (!philo)
		return (error_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE));
	init_philosophers(data, philo);
	pthread_create(&data->check_stop_sim, NULL, &supervisor, (void *)&philo);
	join_threads(data);
	// boel opschonen ??
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
	//stop_simulation - boel opschonen??
	printf("succes\n");
	return (0);
}
