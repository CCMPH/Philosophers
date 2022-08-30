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

// int	initialize_args(int ac, char **av, t_data *data)
// {

// }

int main(int ac, char **av)
{
	//t_data	*data;

	if (ac < 5 || ac > 6)
		return (error_msg(STR_ERR_INPUT_AMMOUNT, NULL, EXIT_FAILURE));
	if(!is_input_valid(ac, av))
		return(EXIT_FAILURE);
	
	// if (initialize_args(ac, av, &data));
	// 	return (1);
	printf("succes\n");
	return (0);
}

// to do:
// initialize functie verder maken