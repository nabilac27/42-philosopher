/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:17:15 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/20 04:09:28 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	Your program(s) must take the following arguments:
		1. number_of_philosophers
		2. time_to_die
		3. time_to_eat
		4. time_to_sleep
		5. number_of_times_each_philosopher_must_eat
*/

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_table(&table, argv);
		init_table(&table);
		exec_dinner(&table);
		// clean_table(&table); // TO-DO
	}
	else
		error_msg("ERROR: Invalid number of arguments");
	return (0);
}
