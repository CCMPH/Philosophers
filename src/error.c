/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: chartema <chartema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 10:17:02 by chartema      #+#    #+#                 */
/*   Updated: 2022/09/07 10:17:15 by chartema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h> //nodig voor exit_failure
#include <stdio.h> //nodig voor printf

int	error_msg(char *str, char *extra_msg, int exit_nr)
{
	if (!extra_msg)
		printf(str, STR_ERROR);
	else
		printf(str, STR_ERROR, extra_msg);
	return (exit_nr);
}

void	*error_null(char *str, char *extra_msg)
{
	error_msg(str, extra_msg, EXIT_FAILURE);
	return (NULL);
}
