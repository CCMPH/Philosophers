

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdbool.h> //nodig voor bool
#include <pthread.h> //nodig voor pthread

# define MAX_PHILOS	200

# define STR_ERROR	"Error:"
# define STR_ERR_INPUT_AMMOUNT	"%s Wrong amount of arguments\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input:[%s] Input contains not only digits.\n"
# define STR_ERR_PHILO	"%s There must be between 1 and 200 philosophers.\n"
# define STR_ERR_ARG_ZERO	"%s Arguments can't be zero.\n"
# define STR_ERR_MAX_INT	"%s Arguments can't be bigger than MAX_INT.\n"
# define STR_ERR_MALLOC	"%s Malloc went wrong.\n"

typedef struct s_data {
	unsigned int	nr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	times_must_eat;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_philo_dead;
}	t_data;

typedef struct s_philo {
	unsigned int	id_philo;
	// unsigned int	times_eaten;
	// unsigned int	last_eaten;
	// unsigned int	left_fork;
	// unsigned int	right_fork;
	t_data			*data;
}	t_philo;

// ERROR //
int	error_msg(char *str, char *extra_msg, int exit_nr);
void	*error_null(char *str, char *extra_msg);

// CHECKS //
bool	is_input_valid(int ac, char **av);
int		convert_str_to_int(char *str);

// UTILS //
unsigned long	get_time(void);

#endif