/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:21:54 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/07 10:37:36 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h> //nodig voor exit_failure
#include <stdio.h> //nodig voor printf
#include <stdbool.h> //nodig voor bool
#include <limits.h> //nodig voor int_MAX
# include <pthread.h> //nodig voor pthread functies

# define MAX_PHILOS	200
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data {
int				nr_philos;
int				time_to_die;
int				time_to_eat;
int				time_to_sleep;
int				times_must_eat;
long			start_time;
bool			dead;

pthread_mutex_t	*forks;
pthread_mutex_t	lock_write;
pthread_mutex_t	lock_check_dead;

t_philo			*philo;
};

struct s_philo {
t_data	*data;
int		philo_id;
int		times_eaten;
long	time_last_meal;
int		fork_left;
int		fork_right;

};


// CHECK INPUT //
bool	is_input_valid(int ac, char **av);

// ERROR //
int	error_msg(char *str, int exit_nr);

// UTILS //
int	convert_str_to_int(char *str);

#endif