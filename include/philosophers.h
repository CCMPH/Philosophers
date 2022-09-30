/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:21:54 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/30 11:51:09 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h> //nodig voor exit_failure
# include <stdio.h> //nodig voor printf
# include <stdbool.h> //nodig voor bool
# include <limits.h> //nodig voor int_MAX
# include <pthread.h> //nodig voor pthread functies
# include <sys/time.h> //nodig voor gettimeofday
# include <unistd.h> //nodig voor usleep


# define MAX_PHILOS	200

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data {
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philos_done_eating;
	long			start_time;
	bool			dead;
	pthread_t		*threads;

	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_dead;

	t_philo			*philo;
};

struct s_philo {
	t_data			*data;
	int				philo_id;
	int				times_eaten;
	long			time_last_meal;
	bool			done_eating;
	int				fork_left;
	int				fork_right;
	pthread_mutex_t	lock_eating;
};

// CHECK INPUT //
bool	is_input_valid(int ac, char **av);

// INITIALIZE //
int		initialize(t_data *data, char **av);

// SIMULATION //
int		start_simulation(t_data *data);

// ACTIONS //
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

// MONITORING //
bool	check_dead(t_data *data);
void	monitoring(t_data *data);

// ERROR //
int		error_msg(char *str, int exit_nr);
int		error_free_data(t_data *data);
bool	destroy_mutex_forks(t_data *data, int index, bool info);
bool	destroy_mutex_write_and_fork(t_data *data, int index, bool info);

// UTILS //
int		convert_str_to_int(char *str);
long	get_time(void);
void	philo_print(t_philo *philo, char *str);
void	join_threads(t_data *data);

#endif