/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:18:49 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/07 10:25:08 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <limits.h> //nodig voor int_MAX

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	// als het mis gaat. Protecten
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	convert_str_to_int(char *str)
{
	unsigned long	nb;
	int				i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}
