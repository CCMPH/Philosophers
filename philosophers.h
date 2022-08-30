

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdbool.h> //nodig voor bool

# define MAX_PHILOS	200

# define STR_ERROR	"Error:"
# define STR_ERR_INPUT_AMMOUNT	"%s Wrong amount of arguments\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input:[%s] Input contains not only digits.\n"
# define STR_ERR_PHILO	"%s There must be between 1 and 200 philosophers.\n"
# define STR_ERR_ARG_ZERO	"%s Arguments can't be zero.\n"
# define STR_ERR_MAX_INT	"%s Arguments can't be bigger than MAX_INT.\n"

typedef struct s_data {
	unsigned int	nr_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}	t_data;

typedef struct s_philo {
	unsigned int	id_philo;
}	t_philo;

// ERROR //
int	error_msg(char *str, char *extra_msg, int exit_nr);

// CHECKS //
bool	is_input_valid(int ac, char **av);

#endif