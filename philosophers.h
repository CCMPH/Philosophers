

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


typedef struct s_data {
	unsigned int	nr_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}	t_data;

typedef struct s_philo {
	unsigned int	id_philo;
}	t_philo;

// UTILS //
int	ft_error(char *str);

#endif